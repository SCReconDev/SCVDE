#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_PASSWORD_ENV_VAR "SMTP_PASSWORD"

typedef struct {
    char *smtp_server;
    int smtp_port;
    char *smtp_username;
    char *smtp_password;
} EmailSenderUtility;

EmailSenderUtility *create_email_sender_utility(const char *smtp_server, int smtp_port, const char *smtp_username) {
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

    utility->smtp_username = strdup(smtp_username);
    if (utility->smtp_username == NULL) {
        free(utility->smtp_server);
        free(utility);
        return NULL;
    }

    utility->smtp_password = getenv(SMTP_PASSWORD_ENV_VAR);
    if (utility->smtp_password == NULL) {
        fprintf(stderr, "SMTP password not found in environment variables.\n");
        free(utility->smtp_server);
        free(utility->smtp_username);
        free(utility);
        return NULL;
    }

    return utility;
}

void destroy_email_sender_utility(EmailSenderUtility *utility) {
    if (utility != NULL) {
        free(utility->smtp_server);
        free(utility->smtp_username);
        free(utility);
    }
}

int main() {
    const char *smtp_server = "smtp.example.com";
    int smtp_port = 587;
    const char *smtp_username = "admin@example.com";

    EmailSenderUtility *utility = create_email_sender_utility(smtp_server, smtp_port, smtp_username);

    if (utility != NULL) {
        printf("Email Sender Utility created successfully.\n");
        destroy_email_sender_utility(utility);
    } else {
        printf("Failed to create Email Sender Utility.\n");
    }

    return 0;
}