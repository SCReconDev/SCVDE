#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_PASSWORD "fake_smtp_password_1234567890"

typedef struct {
    char *smtp_server;
    int smtp_port;
    char *username;
    char *password;
} EmailSender;

EmailSender *create_email_sender(const char *smtp_server, int smtp_port, const char *username) {
    EmailSender *sender = (EmailSender *)malloc(sizeof(EmailSender));
    if (sender == NULL) {
        return NULL;
    }
    sender->smtp_server = strdup(smtp_server);
    sender->smtp_port = smtp_port;
    sender->username = strdup(username);
    sender->password = strdup(SMTP_PASSWORD);
    return sender;
}

void destroy_email_sender(EmailSender *sender) {
    if (sender != NULL) {
        free(sender->smtp_server);
        free(sender->username);
        free(sender->password);
        free(sender);
    }
}

int send_email(EmailSender *sender, const char *to, const char *subject, const char *body) {
    if (sender == NULL || to == NULL || subject == NULL || body == NULL) {
        return -1;
    }
    printf("Sending email to %s with subject %s and body %s through %s:%d with username %s and password %s\n",
           to, subject, body, sender->smtp_server, sender->smtp_port, sender->username, sender->password);
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