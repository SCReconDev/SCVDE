#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_PASSWORD "fake_smtp_password_1234567890"

typedef struct {
    char *smtp_server;
    int smtp_port;
    char *username;
    char *password;
} EmailSenderUtility;

EmailSenderUtility *create_email_sender_utility(const char *smtp_server, int smtp_port, const char *username) {
    EmailSenderUtility *utility = (EmailSenderUtility *)malloc(sizeof(EmailSenderUtility));
    if (utility == NULL) {
        return NULL;
    }

    utility->smtp_server = strdup(smtp_server);
    utility->smtp_port = smtp_port;
    utility->username = strdup(username);
    utility->password = strdup(SMTP_PASSWORD);

    return utility;
}

void destroy_email_sender_utility(EmailSenderUtility *utility) {
    if (utility != NULL) {
        free(utility->smtp_server);
        free(utility->username);
        free(utility->password);
        free(utility);
    }
}

int send_email(EmailSenderUtility *utility, const char *to, const char *subject, const char *body) {
    if (utility == NULL || to == NULL || subject == NULL || body == NULL) {
        return -1;
    }

    printf("Sending email to %s with subject %s and body %s using SMTP server %s:%d with username %s and password %s\n",
           to, subject, body, utility->smtp_server, utility->smtp_port, utility->username, utility->password);
    return 0;
}

int main() {
    EmailSenderUtility *utility = create_email_sender_utility("smtp.example.com", 587, "admin");
    if (utility == NULL) {
        fprintf(stderr, "Failed to create email sender utility\n");
        return 1;
    }

    send_email(utility, "user@example.com", "Test Subject", "Test Body");

    destroy_email_sender_utility(utility);
    return 0;
}