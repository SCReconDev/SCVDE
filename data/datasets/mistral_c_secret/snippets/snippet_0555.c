#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define SMTP_SERVER "smtp.example.com"
#define SMTP_PORT 587
#define SMTP_USER "user@example.com"
#define SMTP_PASS_ENV "SMTP_PASSWORD"

typedef struct {
    CURL *curl;
    char *server;
    int port;
    char *user;
    char *password;
} EmailSender;

EmailSender *create_email_sender() {
    EmailSender *sender = (EmailSender *)malloc(sizeof(EmailSender));
    if (sender == NULL) {
        return NULL;
    }

    sender->server = strdup(SMTP_SERVER);
    sender->port = SMTP_PORT;
    sender->user = strdup(SMTP_USER);
    sender->password = getenv(SMTP_PASS_ENV);

    if (sender->server == NULL || sender->user == NULL || sender->password == NULL) {
        fprintf(stderr, "Memory allocation or environment variable error.\n");
        free(sender->server);
        free(sender->user);
        free(sender);
        return NULL;
    }

    sender->curl = curl_easy_init();
    if (sender->curl == NULL) {
        fprintf(stderr, "Failed to initialize CURL.\n");
        free(sender->server);
        free(sender->user);
        free(sender);
        return NULL;
    }

    return sender;
}

void destroy_email_sender(EmailSender *sender) {
    if (sender != NULL) {
        if (sender->curl != NULL) {
            curl_easy_cleanup(sender->curl);
        }
        free(sender->server);
        free(sender->user);
        free(sender);
    }
}

int main() {
    EmailSender *sender = create_email_sender();
    if (sender == NULL) {
        fprintf(stderr, "Failed to create email sender.\n");
        return 1;
    }

    printf("Email sender created successfully.\n");
    printf("Server: %s\n", sender->server);
    printf("Port: %d\n", sender->port);
    printf("User: %s\n", sender->user);

    destroy_email_sender(sender);
    return 0;
}