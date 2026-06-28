#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    CURL *curl;
    char *smtp_server;
    char *username;
    char *password;
    int port;
} EmailSender;

EmailSender* create_email_sender(const char *smtp_server, const char *username, int port) {
    EmailSender *sender = (EmailSender*)malloc(sizeof(EmailSender));
    sender->smtp_server = strdup(smtp_server);
    sender->username = strdup(username);
    sender->port = port;
    sender->password = getenv("SMTP_PASSWORD");
    if (sender->password == NULL) {
        fprintf(stderr, "SMTP_PASSWORD environment variable not set\n");
        free(sender->smtp_server);
        free(sender->username);
        free(sender);
        return NULL;
    }
    sender->curl = curl_easy_init();
    if (sender->curl == NULL) {
        fprintf(stderr, "Failed to initialize CURL\n");
        free(sender->smtp_server);
        free(sender->username);
        free(sender);
        return NULL;
    }
    return sender;
}

void destroy_email_sender(EmailSender *sender) {
    if (sender != NULL) {
        curl_easy_cleanup(sender->curl);
        free(sender->smtp_server);
        free(sender->username);
        free(sender);
    }
}

int main() {
    EmailSender *sender = create_email_sender("smtp.example.com", "user@example.com", 587);
    if (sender == NULL) {
        return 1;
    }
    printf("Email sender created for server: %s\n", sender->smtp_server);
    destroy_email_sender(sender);
    return 0;
}