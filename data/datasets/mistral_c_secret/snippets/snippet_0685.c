#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    char *smtp_server;
    int smtp_port;
    char *username;
    char *password;
} EmailSenderConfig;

EmailSenderConfig* create_email_sender_config() {
    EmailSenderConfig *config = (EmailSenderConfig*)malloc(sizeof(EmailSenderConfig));
    if (config == NULL) {
        return NULL;
    }

    char *server = getenv("SMTP_SERVER");
    if (server == NULL) {
        fprintf(stderr, "SMTP_SERVER environment variable not set\n");
        free(config);
        return NULL;
    }

    char *port_str = getenv("SMTP_PORT");
    if (port_str == NULL) {
        fprintf(stderr, "SMTP_PORT environment variable not set\n");
        free(config);
        return NULL;
    }

    char *user = getenv("SMTP_USERNAME");
    if (user == NULL) {
        fprintf(stderr, "SMTP_USERNAME environment variable not set\n");
        free(config);
        return NULL;
    }

    char *pass = getenv("SMTP_PASSWORD");
    if (pass == NULL) {
        fprintf(stderr, "SMTP_PASSWORD environment variable not set\n");
        free(config);
        return NULL;
    }

    config->smtp_server = strdup(server);
    if (config->smtp_server == NULL) {
        free(config);
        return NULL;
    }

    config->smtp_port = atoi(port_str);
    config->username = strdup(user);
    if (config->username == NULL) {
        free(config->smtp_server);
        free(config);
        return NULL;
    }

    config->password = strdup(pass);
    if (config->password == NULL) {
        free(config->smtp_server);
        free(config->username);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_email_sender_config(EmailSenderConfig *config) {
    if (config != NULL) {
        if (config->smtp_server != NULL) {
            free(config->smtp_server);
        }
        if (config->username != NULL) {
            free(config->username);
        }
        if (config->password != NULL) {
            free(config->password);
        }
        free(config);
    }
}

int send_email(EmailSenderConfig *config, const char *to, const char *subject, const char *body, char *response_buffer, size_t buffer_size) {
    if (config == NULL || to == NULL || subject == NULL || body == NULL || response_buffer == NULL || buffer_size == 0) {
        return -1;
    }

    CURL *curl = curl_easy_init();
    if (curl == NULL) {
        fprintf(stderr, "Failed to initialize CURL\n");
        return -1;
    }

    char url[1024];
    snprintf(url, 1024, "smtp://%s:%d", config->smtp_server, config->smtp_port);

    struct curl_slist *recipients = NULL;
    recipients = curl_slist_append(recipients, to);

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_USERNAME, config->username);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, config->password);
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, config->username);
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);

    char mail_data[1024];
    snprintf(mail_data, 1024, "From: %s\nTo: %s\nSubject: %s\n\n%s", config->username, to, subject, body);

    curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_READDATA, mail_data);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "Failed to send email: %s\n", curl_easy_strerror(res));
        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
        return -1;
    }

    snprintf(response_buffer, buffer_size, "Email sent to %s", to);

    curl_slist_free_all(recipients);
    curl_easy_cleanup(curl);
    return 0;
}

int main() {
    EmailSenderConfig *config = create_email_sender_config();
    if (config == NULL) {
        return 1;
    }

    char response[1024];
    if (send_email(config, "user@example.com", "Test Subject", "Test Body", response, 1024) != 0) {
        fprintf(stderr, "Failed to send email\n");
        destroy_email_sender_config(config);
        return 1;
    }

    printf("Email Response: %s\n", response);

    destroy_email_sender_config(config);
    return 0;
}