#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_PASSWORD_ENV_VAR "SMTP_PASSWORD"

typedef struct {
    char *smtp_server;
    int smtp_port;
    char *smtp_user;
    char *smtp_password;
    char *from_address;
} EmailSenderUtility;

EmailSenderUtility* create_email_sender_utility(const char *smtp_server, int smtp_port, const char *smtp_user, const char *from_address) {
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

    utility->smtp_user = strdup(smtp_user);
    if (utility->smtp_user == NULL) {
        free(utility->smtp_server);
        free(utility);
        return NULL;
    }

    utility->smtp_password = getenv(SMTP_PASSWORD_ENV_VAR);
    if (utility->smtp_password == NULL) {
        fprintf(stderr, "Error: SMTP password not found in environment variables.\n");
        free(utility->smtp_server);
        free(utility->smtp_user);
        free(utility);
        return NULL;
    }

    utility->from_address = strdup(from_address);
    if (utility->from_address == NULL) {
        free(utility->smtp_server);
        free(utility->smtp_user);
        free(utility);
        return NULL;
    }

    return utility;
}

void destroy_email_sender_utility(EmailSenderUtility *utility) {
    if (utility != NULL) {
        free(utility->smtp_server);
        free(utility->smtp_user);
        free(utility->from_address);
        free(utility);
    }
}

int main() {
    EmailSenderUtility *utility = create_email_sender_utility("smtp.example.com", 587, "user@example.com", "sender@example.com");
    if (utility == NULL) {
        return 1;
    }

    printf("Email Sender Utility created successfully.\n");
    printf("SMTP Server: %s\n", utility->smtp_server);
    printf("SMTP Port: %d\n", utility->smtp_port);
    printf("SMTP User: %s\n", utility->smtp_user);
    printf("SMTP Password: %s\n", utility->smtp_password);
    printf("From Address: %s\n", utility->from_address);

    destroy_email_sender_utility(utility);
    return 0;
}