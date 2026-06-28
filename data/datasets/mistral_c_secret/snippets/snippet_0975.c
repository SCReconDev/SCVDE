#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define SMTP_PASSWORD_ENV_VAR "SMTP_PASSWORD"

typedef struct {
    char *smtp_server;
    int smtp_port;
    char *username;
    char *password;
} EmailSender;

EmailSender* create_email_sender(const char *smtp_server, int smtp_port, const char *username) {
    EmailSender *sender = (EmailSender*)malloc(sizeof(EmailSender));
    if (sender == NULL) {
        return NULL;
    }

    sender->smtp_server = strdup(smtp_server);
    sender->smtp_port = smtp_port;
    sender->username = strdup(username);

    if (sender->smtp_server == NULL || sender->username == NULL) {
        free(sender->smtp_server);
        free(sender->username);
        free(sender);
        return NULL;
    }

    const char *password = getenv(SMTP_PASSWORD_ENV_VAR);
    if (password == NULL) {
        fprintf(stderr, "Error: SMTP password not found in environment variables.\n");
        free(sender->smtp_server);
        free(sender->username);
        free(sender);
        return NULL;
    }

    sender->password = strdup(password);
    if (sender->password == NULL) {
        free(sender->smtp_server);
        free(sender->username);
        free(sender);
        return NULL;
    }

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

int main() {
    EmailSender *sender = create_email_sender("smtp.example.com", 587, "user@example.com");
    if (sender == NULL) {
        return EXIT_FAILURE;
    }

    printf("Email sender created.\n");
    printf("SMTP Server: %s\n", sender->smtp_server);
    printf("SMTP Port: %d\n", sender->smtp_port);
    printf("Username: %s\n", sender->username);

    destroy_email_sender(sender);
    return EXIT_SUCCESS;
}