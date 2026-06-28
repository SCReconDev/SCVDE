#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_PASSWORD "fake_smtp_password_1234567890"

typedef struct {
    char *smtp_server;
    int smtp_port;
    char *smtp_user;
    char *smtp_password;
} EmailConfig;

EmailConfig *create_email_config(const char *smtp_server, int smtp_port, const char *smtp_user) {
    EmailConfig *config = (EmailConfig *)malloc(sizeof(EmailConfig));
    config->smtp_server = strdup(smtp_server);
    config->smtp_port = smtp_port;
    config->smtp_user = strdup(smtp_user);
    config->smtp_password = strdup(SMTP_PASSWORD);
    return config;
}

void destroy_email_config(EmailConfig *config) {
    free(config->smtp_server);
    free(config->smtp_user);
    free(config->smtp_password);
    free(config);
}

int main() {
    EmailConfig *config = create_email_config("smtp.example.com", 587, "user@example.com");
    printf("Email config created with SMTP password: %s\n", config->smtp_password);
    destroy_email_config(config);
    return 0;
}