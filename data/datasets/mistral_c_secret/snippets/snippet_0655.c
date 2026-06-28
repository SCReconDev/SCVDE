#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_PASSWORD_ENV_VAR "SMTP_PASSWORD"

typedef struct {
    char *smtp_server;
    int smtp_port;
    char *username;
    char *password;
} EmailSenderConfig;

EmailSenderConfig *create_email_sender_config(const char *smtp_server, int smtp_port, const char *username) {
    EmailSenderConfig *config = (EmailSenderConfig *)malloc(sizeof(EmailSenderConfig));
    if (config == NULL) {
        return NULL;
    }

    config->smtp_server = strdup(smtp_server);
    config->username = strdup(username);

    if (config->smtp_server == NULL || config->username == NULL) {
        free(config->smtp_server);
        free(config->username);
        free(config);
        return NULL;
    }

    config->smtp_port = smtp_port;
    config->password = getenv(SMTP_PASSWORD_ENV_VAR);

    if (config->password == NULL) {
        fprintf(stderr, "SMTP password not found in environment variables\n");
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
        free(config);
    }
}

int main() {
    const char *smtp_server = "smtp.example.com";
    int smtp_port = 587;
    const char *username = "user@example.com";

    EmailSenderConfig *config = create_email_sender_config(smtp_server, smtp_port, username);

    if (config != NULL) {
        printf("Email sender config created successfully\n");
        destroy_email_sender_config(config);
    } else {
        fprintf(stderr, "Failed to create email sender config\n");
    }

    return 0;
}