#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *smtp_server;
    int smtp_port;
    char *smtp_username;
    char *smtp_password;
} EmailConfig;

EmailConfig *create_email_config() {
    EmailConfig *config = (EmailConfig *)malloc(sizeof(EmailConfig));
    if (config == NULL) {
        return NULL;
    }

    config->smtp_server = getenv("SMTP_SERVER");
    if (config->smtp_server == NULL) {
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
    config->smtp_port = atoi(port_str);

    config->smtp_username = getenv("SMTP_USERNAME");
    if (config->smtp_username == NULL) {
        fprintf(stderr, "SMTP_USERNAME environment variable not set\n");
        free(config);
        return NULL;
    }

    config->smtp_password = getenv("SMTP_PASSWORD");
    if (config->smtp_password == NULL) {
        fprintf(stderr, "SMTP_PASSWORD environment variable not set\n");
        free(config);
        return NULL;
    }

    return config;
}

void destroy_email_config(EmailConfig *config) {
    if (config != NULL) {
        free(config);
    }
}

int main() {
    EmailConfig *config = create_email_config();
    if (config == NULL) {
        return 1;
    }

    printf("Email Configuration:\n");
    printf("SMTP Server: %s\n", config->smtp_server);
    printf("SMTP Port: %d\n", config->smtp_port);
    printf("SMTP Username: %s\n", config->smtp_username);
    printf("SMTP Password: %s\n", config->smtp_password);

    destroy_email_config(config);
    return 0;
}