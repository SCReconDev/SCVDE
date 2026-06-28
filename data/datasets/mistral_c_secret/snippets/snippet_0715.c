#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define SMTP_PASSWORD_ENV_VAR "SMTP_PASSWORD"

typedef struct {
    char *smtp_server;
    int smtp_port;
    char *username;
    char *password;
    char *from;
} EmailSenderConfig;

EmailSenderConfig* create_email_sender_config(const char *smtp_server, int smtp_port, const char *username, const char *from) {
    EmailSenderConfig *config = (EmailSenderConfig*)malloc(sizeof(EmailSenderConfig));
    if (config == NULL) {
        return NULL;
    }

    config->smtp_server = strdup(smtp_server);
    config->smtp_port = smtp_port;
    config->username = strdup(username);
    config->from = strdup(from);

    if (config->smtp_server == NULL || config->username == NULL || config->from == NULL) {
        free(config->smtp_server);
        free(config->username);
        free(config->from);
        free(config);
        return NULL;
    }

    char *password = getenv(SMTP_PASSWORD_ENV_VAR);
    if (password == NULL) {
        fprintf(stderr, "SMTP password not found in environment variables\n");
        free(config->smtp_server);
        free(config->username);
        free(config->from);
        free(config);
        return NULL;
    }

    config->password = strdup(password);
    if (config->password == NULL) {
        free(config->smtp_server);
        free(config->username);
        free(config->from);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_email_sender_config(EmailSenderConfig *config) {
    if (config != NULL) {
        free(config->smtp_server);
        free(config->username);
        free(config->password);
        free(config->from);
        free(config);
    }
}

void send_email(EmailSenderConfig *config, const char *to, const char *subject, const char *body) {
    if (config == NULL) {
        fprintf(stderr, "Invalid email sender configuration\n");
        return;
    }

    CURL *curl = curl_easy_init();
    if (curl == NULL) {
        fprintf(stderr, "Failed to initialize CURL\n");
        return;
    }

    char url[256];
    snprintf(url, sizeof(url), "smtp://%s:%d", config->smtp_server, config->smtp_port);

    struct curl_slist *recipients = NULL;
    recipients = curl_slist_append(recipients, to);

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_USERNAME, config->username);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, config->password);
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, config->from);
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);

    curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_READDATA, NULL);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "Failed to send email: %s\n", curl_easy_strerror(res));
    } else {
        printf("Email sent successfully\n");
    }

    curl_slist_free_all(recipients);
    curl_easy_cleanup(curl);
}

int main() {
    EmailSenderConfig *config = create_email_sender_config("smtp.example.com", 587, "user@example.com", "sender@example.com");
    if (config == NULL) {
        fprintf(stderr, "Failed to create email sender configuration\n");
        return 1;
    }

    send_email(config, "recipient@example.com", "Test Subject", "Test Body");
    destroy_email_sender_config(config);

    return 0;
}