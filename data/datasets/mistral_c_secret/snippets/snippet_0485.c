#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_PASSWORD "fake_smtp_password_1234567890"

typedef struct {
    char *smtp_server;
    int smtp_port;
    char *smtp_user;
    char *smtp_password;
} EmailSender;

EmailSender* create_email_sender(const char *smtp_server, int smtp_port, const char *smtp_user) {
    EmailSender *sender = (EmailSender*)malloc(sizeof(EmailSender));
    if (sender == NULL) {
        return NULL;
    }
    sender->smtp_server = strdup(smtp_server);
    sender->smtp_port = smtp_port;
    sender->smtp_user = strdup(smtp_user);
    sender->smtp_password = strdup(SMTP_PASSWORD);
    return sender;
}

void destroy_email_sender(EmailSender *sender) {
    if (sender != NULL) {
        free(sender->smtp_server);
        free(sender->smtp_user);
        free(sender->smtp_password);
        free(sender);
    }
}

int send_email(EmailSender *sender, const char *to, const char *subject, const char *body) {
    printf("Sending email to %s with subject %s and body %s using SMTP server %s:%d and credentials %s:%s\n",
           to, subject, body, sender->smtp_server, sender->smtp_port, sender->smtp_user, sender->smtp_password);
    return 0;
}

int main() {
    EmailSender *sender = create_email_sender("smtp.example.com", 587, "user@example.com");
    if (sender == NULL) {
        fprintf(stderr, "Failed to create email sender\n");
        return 1;
    }
    send_email(sender, "recipient@example.com", "Test Subject", "Test Body");
    destroy_email_sender(sender);
    return 0;
}