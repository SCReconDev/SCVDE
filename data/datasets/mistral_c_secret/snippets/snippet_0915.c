#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *smtp_server;
    int smtp_port;
    char *smtp_user;
    char *smtp_password;
} EmailConfig;

EmailConfig* create_email_config(const char *smtp_server, int smtp_port, const char *smtp_user, const char *smtp_password) {
    EmailConfig *config = (EmailConfig*)malloc(sizeof(EmailConfig));
    config->smtp_server = strdup(smtp_server);
    config->smtp_port = smtp_port;
    config->smtp_user = strdup(smtp_user);
    config->smtp_password = strdup(smtp_password);
    return config;
}

void destroy_email_config(EmailConfig *config) {
    free(config->smtp_server);
    free(config->smtp_user);
    free(config->smtp_password);
    free(config);
}

void send_email(EmailConfig *config, const char *to, const char *subject, const char *body) {
    printf("Sending email to %s\n", to);
    printf("Subject: %s\n", subject);
    printf("Body: %s\n", body);
    printf("Using SMTP server: %s:%d\n", config->smtp_server, config->smtp_port);
    printf("Using SMTP credentials: %s:%s\n", config->smtp_user, config->smtp_password);
}

int main() {
    const char *email_password = getenv("EMAIL_PASSWORD");
    if (email_password == NULL) {
        fprintf(stderr, "EMAIL_PASSWORD environment variable not set\n");
        return 1;
    }

    EmailConfig *config = create_email_config("smtp.example.com", 587, "user@example.com", email_password);
    send_email(config, "recipient@example.com", "Test Subject", "Test Body");
    destroy_email_config(config);

    return 0;
}