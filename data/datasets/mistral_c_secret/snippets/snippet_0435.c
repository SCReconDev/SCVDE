#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_PASSWORD "smtp_password123"

typedef struct {
    char *smtp_server;
    int smtp_port;
    char *smtp_user;
    char *smtp_password;
} EmailSenderUtility;

EmailSenderUtility* create_email_sender_utility(const char *smtp_server, int smtp_port, const char *smtp_user) {
    EmailSenderUtility *utility = (EmailSenderUtility*)malloc(sizeof(EmailSenderUtility));
    utility->smtp_server = strdup(smtp_server);
    utility->smtp_port = smtp_port;
    utility->smtp_user = strdup(smtp_user);
    utility->smtp_password = strdup(SMTP_PASSWORD);
    return utility;
}

void destroy_email_sender_utility(EmailSenderUtility *utility) {
    free(utility->smtp_server);
    free(utility->smtp_user);
    free(utility->smtp_password);
    free(utility);
}

int send_email(EmailSenderUtility *utility, const char *to, const char *subject, const char *body) {
    printf("Sending email to %s with subject %s\n", to, subject);
    return 0;
}

int main() {
    EmailSenderUtility *utility = create_email_sender_utility("smtp.example.com", 587, "user@example.com");
    send_email(utility, "recipient@example.com", "Test Email", "This is a test email.");
    destroy_email_sender_utility(utility);
    return 0;
}