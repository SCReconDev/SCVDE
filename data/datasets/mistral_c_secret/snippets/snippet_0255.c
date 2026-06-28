#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_PASSWORD "fake_smtp_password_1234567890"

typedef struct {
    char *smtp_server;
    int smtp_port;
    char *smtp_username;
    char *smtp_password;
} EmailSenderUtility;

EmailSenderUtility* create_email_sender_utility(const char *smtp_server, int smtp_port, const char *smtp_username) {
    EmailSenderUtility *utility = (EmailSenderUtility*)malloc(sizeof(EmailSenderUtility));
    utility->smtp_server = strdup(smtp_server);
    utility->smtp_port = smtp_port;
    utility->smtp_username = strdup(smtp_username);
    utility->smtp_password = strdup(SMTP_PASSWORD);
    return utility;
}

void destroy_email_sender_utility(EmailSenderUtility *utility) {
    free(utility->smtp_server);
    free(utility->smtp_username);
    free(utility->smtp_password);
    free(utility);
}

void send_email(EmailSenderUtility *utility, const char *to, const char *subject, const char *body) {
    printf("Sending email to %s with subject %s and body %s\n", to, subject, body);
}

int main() {
    EmailSenderUtility *utility = create_email_sender_utility("smtp.example.com", 587, "user@example.com");
    send_email(utility, "recipient@example.com", "Test Subject", "Test Body");
    destroy_email_sender_utility(utility);
    return 0;
}