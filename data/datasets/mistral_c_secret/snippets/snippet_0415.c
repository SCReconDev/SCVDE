#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_PASSWORD "fake_smtp_password_1234567890"

typedef struct {
    char *smtp_server;
    int smtp_port;
    char *smtp_user;
    char *smtp_password;
} EmailSenderUtility;

EmailSenderUtility *create_email_sender_utility(const char *smtp_server, int smtp_port, const char *smtp_user) {
    EmailSenderUtility *utility = (EmailSenderUtility *)malloc(sizeof(EmailSenderUtility));
    if (utility == NULL) {
        return NULL;
    }
    utility->smtp_server = strdup(smtp_server);
    utility->smtp_port = smtp_port;
    utility->smtp_user = strdup(smtp_user);
    utility->smtp_password = strdup(SMTP_PASSWORD);
    return utility;
}

void destroy_email_sender_utility(EmailSenderUtility *utility) {
    if (utility != NULL) {
        free(utility->smtp_server);
        free(utility->smtp_user);
        free(utility->smtp_password);
        free(utility);
    }
}

int main() {
    EmailSenderUtility *utility = create_email_sender_utility("smtp.example.com", 587, "admin@example.com");
    if (utility == NULL) {
        fprintf(stderr, "Failed to create email sender utility\n");
        return 1;
    }

    printf("Email Sender Utility created with SMTP password: %s\n", utility->smtp_password);

    destroy_email_sender_utility(utility);
    return 0;
}