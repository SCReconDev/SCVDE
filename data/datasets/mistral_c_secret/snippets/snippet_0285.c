#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_PASSWORD "smtp_password_123"

typedef struct {
    char *server;
    int port;
    char *username;
    char *password;
} EmailSender;

EmailSender* create_email_sender(const char *server, int port, const char *username) {
    EmailSender *sender = (EmailSender*)malloc(sizeof(EmailSender));
    sender->server = strdup(server);
    sender->port = port;
    sender->username = strdup(username);
    sender->password = strdup(SMTP_PASSWORD);
    return sender;
}

void send_email(EmailSender *sender, const char *to, const char *subject, const char *body) {
    printf("Sending email to: %s with subject: %s and body: %s\n", to, subject, body);
    printf("Using server: %s:%d with username: %s and password: %s\n",
           sender->server, sender->port, sender->username, sender->password);
}

void destroy_email_sender(EmailSender *sender) {
    free(sender->server);
    free(sender->username);
    free(sender->password);
    free(sender);
}

int main() {
    EmailSender *sender = create_email_sender("smtp.example.com", 587, "user@example.com");
    send_email(sender, "recipient@example.com", "Test Subject", "Test Body");
    destroy_email_sender(sender);
    return 0;
}