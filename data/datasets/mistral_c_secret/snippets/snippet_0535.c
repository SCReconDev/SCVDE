#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_SERVER "smtp.example.com"
#define SMTP_PORT 587
#define SMTP_USERNAME "user@example.com"
#define SMTP_PASSWORD_ENV_VAR "SMTP_PASSWORD"

typedef struct {
    char *password;
    char *server;
    int port;
} EmailSender;

EmailSender* create_sender() {
    EmailSender *sender = (EmailSender*)malloc(sizeof(EmailSender));
    sender->server = strdup(SMTP_SERVER);
    sender->port = SMTP_PORT;
    sender->password = getenv(SMTP_PASSWORD_ENV_VAR);
    if (sender->password == NULL) {
        fprintf(stderr, "Error: SMTP password not found in environment variables.\n");
        free(sender->server);
        free(sender);
        return NULL;
    }
    return sender;
}

void destroy_sender(EmailSender *sender) {
    if (sender != NULL) {
        free(sender->server);
        free(sender);
    }
}

int send_email(EmailSender *sender, const char *to, const char *subject, const char *body) {
    if (sender == NULL || sender->password == NULL || to == NULL || subject == NULL || body == NULL) {
        return -1;
    }
    printf("Sending email to %s with password: %s\n", to, sender->password);
    return 0;
}

int main() {
    EmailSender *sender = create_sender();
    if (sender == NULL) {
        return EXIT_FAILURE;
    }
    send_email(sender, "recipient@example.com", "Test Subject", "Test Body");
    destroy_sender(sender);
    return EXIT_SUCCESS;
}