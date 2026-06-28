#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_PASSWORD "fake_smtp_password_1234567890"

typedef struct {
    char *smtp_server;
    int smtp_port;
    char *username;
    char *password;
} EmailSenderConfig;

EmailSenderConfig* create_email_sender_config(const char *smtp_server, int smtp_port, const char *username) {
    EmailSenderConfig *config = (EmailSenderConfig*)malloc(sizeof(EmailSenderConfig));
    config->smtp_server = strdup(smtp_server);
    config->smtp_port = smtp_port;
    config->username = strdup(username);
    config->password = strdup(SMTP_PASSWORD);
    return config;
}

void send_email(EmailSenderConfig *config, const char *to, const char *subject, const char *body) {
    printf("Sending email to %s with subject %s using SMTP server %s:%d\n", to, subject, config->smtp_server, config->smtp_port);
    printf("Using username %s and password %s\n", config->username, config->password);
}

void destroy_email_sender_config(EmailSenderConfig *config) {
    free(config->smtp_server);
    free(config->username);
    free(config->password);
    free(config);
}

int main() {
    EmailSenderConfig *config = create_email_sender_config("smtp.example.com", 587, "user@example.com");
    send_email(config, "recipient@example.com", "Test Subject", "Test Body");
    destroy_email_sender_config(config);
    return 0;
}