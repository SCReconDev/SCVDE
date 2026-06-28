#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define SMTP_SERVER "smtp.example.com"
#define SMTP_PORT 587
#define SMTP_USER "user@example.com"
#define SMTP_PASSWORD_ENV_VAR "SMTP_PASSWORD"

typedef struct {
    CURL *curl;
    char *server;
    int port;
    char *user;
    char *password;
} EmailSender;

EmailSender* create_email_sender(const char *server, int port, const char *user) {
    EmailSender *sender = (EmailSender*)malloc(sizeof(EmailSender));
    if (sender == NULL) {
        return NULL;
    }

    sender->server = strdup(server);
    sender->user = strdup(user);
    sender->port = port;

    if (sender->server == NULL || sender->user == NULL) {
        free(sender->server);
        free(sender->user);
        free(sender);
        return NULL;
    }

    sender->password = getenv(SMTP_PASSWORD_ENV_VAR);
    if (sender->password == NULL) {
        fprintf(stderr, "Error: SMTP password not found in environment variables.\n");
        free(sender->server);
        free(sender->user);
        free(sender);
        return NULL;
    }

    sender->curl = curl_easy_init();
    if (sender->curl == NULL) {
        fprintf(stderr, "Error: cURL initialization failed.\n");
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
        if (sender->server != NULL) {
            free(sender->server);
        }
        if (sender->user != NULL) {
            free(sender->user);
        }
        free(sender);
    }
}

int main() {
    EmailSender *sender = create_email_sender(SMTP_SERVER, SMTP_PORT, SMTP_USER);
    if (sender == NULL) {
        return 1;
    }

    printf("Email sender created successfully.\n");
    printf("Server: %s\n", sender->server);
    printf("Port: %d\n", sender->port);
    printf("User: %s\n", sender->user);
    printf("Password: %s\n", sender->password);

    destroy_email_sender(sender);
    return 0;
}