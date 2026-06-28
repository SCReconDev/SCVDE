#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    char *smtp_server;
    char *username;
    char *from;
    char *to;
    char *subject;
    char *body;
} EmailConfig;

EmailConfig* create_email_config(const char *smtp_server, const char *username, const char *from, const char *to, const char *subject, const char *body) {
    EmailConfig *config = (EmailConfig*)malloc(sizeof(EmailConfig));
    if (config == NULL) {
        return NULL;
    }

    config->smtp_server = strdup(smtp_server);
    if (config->smtp_server == NULL) {
        free(config);
        return NULL;
    }

    config->username = strdup(username);
    if (config->username == NULL) {
        free(config->smtp_server);
        free(config);
        return NULL;
    }

    config->from = strdup(from);
    if (config->from == NULL) {
        free(config->username);
        free(config->smtp_server);
        free(config);
        return NULL;
    }

    config->to = strdup(to);
    if (config->to == NULL) {
        free(config->from);
        free(config->username);
        free(config->smtp_server);
        free(config);
        return NULL;
    }

    config->subject = strdup(subject);
    if (config->subject == NULL) {
        free(config->to);
        free(config->from);
        free(config->username);
        free(config->smtp_server);
        free(config);
        return NULL;
    }

    config->body = strdup(body);
    if (config->body == NULL) {
        free(config->subject);
        free(config->to);
        free(config->from);
        free(config->username);
        free(config->smtp_server);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_email_config(EmailConfig *config) {
    if (config != NULL) {
        free(config->smtp_server);
        free(config->username);
        free(config->from);
        free(config->to);
        free(config->subject);
        free(config->body);
        free(config);
    }
}

int send_email(EmailConfig *config) {
    if (config == NULL) {
        return -1;
    }

    CURL *curl = curl_easy_init();
    if (curl == NULL) {
        return -1;
    }

    const char *password = getenv("SMTP_PASSWORD");
    if (password == NULL) {
        fprintf(stderr, "SMTP_PASSWORD environment variable not set.\n");
        curl_easy_cleanup(curl);
        return -1;
    }

    char url[1024];
    snprintf(url, sizeof(url), "smtp://%s", config->smtp_server);

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_USERNAME, config->username);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, config->from);

    struct curl_slist *recipients = NULL;
    recipients = curl_slist_append(recipients, config->to);
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

    char message[2048];
    snprintf(message, sizeof(message), "From: %s\nTo: %s\nSubject: %s\n\n%s", config->from, config->to, config->subject, config->body);

    curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_READDATA, message);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "Failed to send email: %s\n", curl_easy_strerror(res));
        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
        return -1;
    }

    curl_slist_free_all(recipients);
    curl_easy_cleanup(curl);

    return 0;
}

int main() {
    EmailConfig *config = create_email_config("smtp.example.com", "user@example.com", "user@example.com", "recipient@example.com", "Test Email", "This is a test email.");
    if (config == NULL) {
        fprintf(stderr, "Failed to create email config.\n");
        return 1;
    }

    if (send_email(config) != 0) {
        fprintf(stderr, "Failed to send email.\n");
        destroy_email_config(config);
        return 1;
    }

    destroy_email_config(config);

    return 0;
}