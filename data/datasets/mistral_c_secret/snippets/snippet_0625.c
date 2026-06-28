#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    char *smtp_server;
    char *smtp_username;
    char *smtp_password;
    int smtp_port;
} EmailSenderConfig;

EmailSenderConfig* create_email_sender_config(const char *smtp_server, const char *smtp_username, const char *smtp_password, int smtp_port) {
    EmailSenderConfig *config = (EmailSenderConfig*)malloc(sizeof(EmailSenderConfig));
    if (config == NULL) {
        return NULL;
    }

    config->smtp_server = strdup(smtp_server);
    config->smtp_username = strdup(smtp_username);
    config->smtp_password = strdup(smtp_password);
    config->smtp_port = smtp_port;

    if (config->smtp_server == NULL || config->smtp_username == NULL || config->smtp_password == NULL) {
        free(config->smtp_server);
        free(config->smtp_username);
        free(config->smtp_password);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_email_sender_config(EmailSenderConfig *config) {
    if (config != NULL) {
        free(config->smtp_server);
        free(config->smtp_username);
        free(config->smtp_password);
        free(config);
    }
}

int send_email(EmailSenderConfig *config, const char *to, const char *subject, const char *body) {
    if (config == NULL || config->smtp_server == NULL || config->smtp_username == NULL || config->smtp_password == NULL) {
        return -1;
    }

    CURL *curl;
    CURLcode res = CURLE_OK;

    curl = curl_easy_init();
    if (curl) {
        char url[256];
        snprintf(url, sizeof(url), "smtp://%s:%d", config->smtp_server, config->smtp_port);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_USERNAME, config->smtp_username);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, config->smtp_password);
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, config->smtp_username);

        struct curl_slist *recipients = NULL;
        recipients = curl_slist_append(recipients, to);
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "Failed to send email: %s\n", curl_easy_strerror(res));
        }

        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }

    return res == CURLE_OK ? 0 : -1;
}

int main() {
    const char *smtp_server = getenv("SMTP_SERVER");
    const char *smtp_username = getenv("SMTP_USERNAME");
    const char *smtp_password = getenv("SMTP_PASSWORD");
    const char *smtp_port_str = getenv("SMTP_PORT");

    if (smtp_server == NULL || smtp_username == NULL || smtp_password == NULL || smtp_port_str == NULL) {
        fprintf(stderr, "SMTP environment variables not set\n");
        return 1;
    }

    int smtp_port = atoi(smtp_port_str);

    EmailSenderConfig *config = create_email_sender_config(smtp_server, smtp_username, smtp_password, smtp_port);
    if (config == NULL) {
        fprintf(stderr, "Failed to create email sender config\n");
        return 1;
    }

    if (send_email(config, "recipient@example.com", "Test Subject", "Test Body") != 0) {
        fprintf(stderr, "Failed to send email\n");
        destroy_email_sender_config(config);
        return 1;
    }

    destroy_email_sender_config(config);
    return 0;
}