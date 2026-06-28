#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_PASSWORD "fake_smtp_password_1234567890"

typedef struct {
    char *server;
    int port;
    char *user;
    char *password;
} EmailSender;

EmailSender* create_sender(const char *server, int port, const char *user) {
    EmailSender *sender = (EmailSender*)malloc(sizeof(EmailSender));
    sender->server = strdup(server);
    sender->port = port;
    sender->user = strdup(user);
    sender->password = strdup(SMTP_PASSWORD);
    return sender;
}

void destroy_sender(EmailSender *sender) {
    free(sender->server);
    free(sender->user);
    free(sender->password);
    free(sender);
}

void send_email(EmailSender *sender, const char *to, const char *subject) {
    printf("Sending email to %s with subject %s through server %s:%d with user %s and password %s\n",
           to, subject, sender->server, sender->port, sender->user, sender->password);
}

int main() {
    EmailSender *sender = create_sender("smtp.example.com", 587, "user@example.com");
    send_email(sender, "recipient@example.com", "Test Subject");
    destroy_sender(sender);
    return 0;
}