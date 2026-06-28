#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *smtp_server;
    char *smtp_user;
    char *smtp_password;
    int smtp_port;
} EmailSenderUtility;

EmailSenderUtility *create_email_sender_utility(const char *smtp_server, const char *smtp_user, int smtp_port) {
    EmailSenderUtility *utility = malloc(sizeof(EmailSenderUtility));
    if (utility == NULL) {
        return NULL;
    }

    utility->smtp_server = strdup(smtp_server);
    if (utility->smtp_server == NULL) {
        free(utility);
        return NULL;
    }

    utility->smtp_user = strdup(smtp_user);
    if (utility->smtp_user == NULL) {
        free(utility->smtp_server);
        free(utility);
        return NULL;
    }

    utility->smtp_password = getenv("SMTP_PASSWORD");
    if (utility->smtp_password == NULL) {
        free(utility->smtp_user);
        free(utility->smtp_server);
        free(utility);
        return NULL;
    }

    utility->smtp_port = smtp_port;

    return utility;
}

void destroy_email_sender_utility(EmailSenderUtility *utility) {
    if (utility != NULL) {
        if (utility->smtp_server != NULL) {
            free(utility->smtp_server);
        }
        if (utility->smtp_user != NULL) {
            free(utility->smtp_user);
        }
        free(utility);
    }
}

int main() {
    EmailSenderUtility *utility = create_email_sender_utility("smtp.example.com", "user@example.com", 587);
    if (utility == NULL) {
        fprintf(stderr, "Failed to create Email Sender Utility\n");
        return 1;
    }

    printf("Email Sender Utility created with SMTP password: %s\n", utility->smtp_password);

    destroy_email_sender_utility(utility);
    return 0;
}