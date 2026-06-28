#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_PASSWORD "smtp_password_123"

typedef struct {
    char *smtp_server;
    int smtp_port;
    char *smtp_user;
    char *smtp_password;
} EmailSenderUtility;

EmailSenderUtility *create_utility(const char *smtp_server, int smtp_port, const char *smtp_user) {
    EmailSenderUtility *utility = (EmailSenderUtility *)malloc(sizeof(EmailSenderUtility));
    utility->smtp_server = strdup(smtp_server);
    utility->smtp_port = smtp_port;
    utility->smtp_user = strdup(smtp_user);
    utility->smtp_password = strdup(SMTP_PASSWORD);
    return utility;
}

void destroy_utility(EmailSenderUtility *utility) {
    free(utility->smtp_server);
    free(utility->smtp_user);
    free(utility->smtp_password);
    free(utility);
}

void send_email(EmailSenderUtility *utility, const char *to, const char *subject, const char *body) {
    printf("Sending email to: %s with subject: %s and body: %s using SMTP server: %s:%d and credentials: %s:%s\n",
           to, subject, body, utility->smtp_server, utility->smtp_port, utility->smtp_user, utility->smtp_password);
}

int main() {
    EmailSenderUtility *utility = create_utility("smtp.example.com", 587, "user@example.com");
    send_email(utility, "recipient@example.com", "Test Subject", "Test Body");
    destroy_utility(utility);
    return 0;
}