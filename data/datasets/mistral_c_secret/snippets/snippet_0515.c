#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    char *smtp_server;
    int smtp_port;
    char *smtp_user;
    char *smtp_password;
} EmailSenderUtility;

EmailSenderUtility* create_email_sender_utility(const char *smtp_server, int smtp_port, const char *smtp_user) {
    EmailSenderUtility *utility = (EmailSenderUtility*)malloc(sizeof(EmailSenderUtility));
    if (utility == NULL) {
        return NULL;
    }

    utility->smtp_server = strdup(smtp_server);
    utility->smtp_user = strdup(smtp_user);
    if (utility->smtp_server == NULL || utility->smtp_user == NULL) {
        free(utility->smtp_server);
        free(utility->smtp_user);
        free(utility);
        return NULL;
    }

    utility->smtp_port = smtp_port;

    utility->smtp_password = getenv("SMTP_PASSWORD");
    if (utility->smtp_password == NULL) {
        fprintf(stderr, "SMTP_PASSWORD environment variable not set.\n");
        free(utility->smtp_server);
        free(utility->smtp_user);
        free(utility);
        return NULL;
    }

    return utility;
}

void destroy_email_sender_utility(EmailSenderUtility *utility) {
    if (utility != NULL) {
        if (utility->smtp_server != NULL) {
            free(utility->smtp_server);
        }
        if (utility->smtp_user != NULL) {
            free(utility->smtp_user);
        }
        free(utility);
    }
}

static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *userp) {
    char *data = (char*)userp;
    size_t data_len = strlen(data);

    if (size * nmemb < 1) {
        return 0;
    }

    if (data_len > 0) {
        size_t copy_len = size * nmemb;
        if (copy_len > data_len) {
            copy_len = data_len;
        }
        memcpy(ptr, data, copy_len);
        data += copy_len;
        data_len -= copy_len;
        return copy_len;
    }

    return 0;
}

int send_email(EmailSenderUtility *utility, const char *to, const char *subject, const char *body) {
    CURL *curl;
    CURLcode res;
    char url[256];
    char from[256];
    char auth[256];
    char data[1024];

    if (utility == NULL || to == NULL || subject == NULL || body == NULL) {
        return -1;
    }

    snprintf(url, sizeof(url), "smtp://%s:%d", utility->smtp_server, utility->smtp_port);
    snprintf(from, sizeof(from), "From: %s\r\nTo: %s\r\nSubject: %s\r\n\r\n%s", utility->smtp_user, to, subject, body);
    snprintf(auth, sizeof(auth), "USER %s\r\nPASS %s\r\n", utility->smtp_user, utility->smtp_password);
    snprintf(data, sizeof(data), "MAIL FROM:<%s>\r\nRCPT TO:<%s>\r\nDATA\r\n%s\r\n.\r\nQUIT\r\n", utility->smtp_user, to, from);

    curl = curl_easy_init();
    if (curl == NULL) {
        return -1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_USERNAME, utility->smtp_user);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, utility->smtp_password);
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
    curl_easy_setopt(curl, CURLOPT_READDATA, data);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        return -1;
    }

    curl_easy_cleanup(curl);

    return 0;
}