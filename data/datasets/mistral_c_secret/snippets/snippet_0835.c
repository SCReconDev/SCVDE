#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    char *smtp_server;
    int smtp_port;
    char *username;
    char *password;
} EmailSenderUtility;

EmailSenderUtility *create_email_sender_utility(const char *smtp_server, int smtp_port, const char *username, const char *password) {
    EmailSenderUtility *utility = (EmailSenderUtility *)malloc(sizeof(EmailSenderUtility));
    if (utility == NULL) {
        return NULL;
    }

    utility->smtp_server = strdup(smtp_server);
    if (utility->smtp_server == NULL) {
        free(utility);
        return NULL;
    }

    utility->smtp_port = smtp_port;

    utility->username = strdup(username);
    if (utility->username == NULL) {
        free(utility->smtp_server);
        free(utility);
        return NULL;
    }

    utility->password = strdup(password);
    if (utility->password == NULL) {
        free(utility->smtp_server);
        free(utility->username);
        free(utility);
        return NULL;
    }

    return utility;
}

void destroy_email_sender_utility(EmailSenderUtility *utility) {
    if (utility != NULL) {
        free(utility->smtp_server);
        free(utility->username);
        free(utility->password);
        free(utility);
    }
}

int send_email(EmailSenderUtility *utility, const char *to, const char *subject, const char *body) {
    if (utility == NULL || to == NULL || subject == NULL || body == NULL) {
        return -1;
    }

    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {
        char url[256];
        snprintf(url, sizeof(url), "smtp://%s:%d", utility->smtp_server, utility->smtp_port);

        struct curl_slist *recipients = NULL;
        recipients = curl_slist_append(recipients, to);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, utility->username);
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
        curl_easy_setopt(curl, CURLOPT_USERNAME, utility->username);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, utility->password);
        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: text/plain");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_READDATA, NULL);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            curl_slist_free_all(recipients);
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return -1;
        }

        curl_slist_free_all(recipients);
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return 0;
}

int main() {
    const char *smtp_password = getenv("SMTP_PASSWORD");
    if (smtp_password == NULL) {
        fprintf(stderr, "SMTP_PASSWORD environment variable not set\n");
        return 1;
    }

    EmailSenderUtility *utility = create_email_sender_utility("smtp.example.com", 587, "user@example.com", smtp_password);
    if (utility == NULL) {
        fprintf(stderr, "Failed to create email sender utility\n");
        return 1;
    }

    send_email(utility, "recipient@example.com", "Test Subject", "Test Body");

    destroy_email_sender_utility(utility);

    return 0;
}