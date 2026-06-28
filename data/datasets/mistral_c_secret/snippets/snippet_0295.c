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
    if (sender == NULL) {
        return NULL;
    }

    sender->server = strdup(server);
    sender->port = port;
    sender->username = strdup(username);
    sender->password = strdup(SMTP_PASSWORD);

    return sender;
}

void destroy_email_sender(EmailSender *sender) {
    if (sender != NULL) {
        free(sender->server);
        free(sender->username);
        free(sender->password);
        free(sender);
    }
}

int main() {
    EmailSender *sender = create_email_sender("smtp.example.com", 587, "user@example.com");
    if (sender == NULL) {
        fprintf(stderr, "Failed to create email sender\n");
        return 1;
    }

    printf("Email Sender created with password: %s\n", sender->password);

    destroy_email_sender(sender);
    return 0;
}