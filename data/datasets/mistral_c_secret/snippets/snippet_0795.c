#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    CURL *curl;
    char *smtp_server;
    char *smtp_port;
    char *smtp_user;
    char *smtp_password;
} EmailSenderUtility;

EmailSenderUtility *create_email_sender_utility(const char *smtp_server, const char *smtp_port, const char *smtp_user) {
    EmailSenderUtility *utility = malloc(sizeof(EmailSenderUtility));
    if (utility == NULL) {
        return NULL;
    }

    utility->smtp_server = strdup(smtp_server);
    utility->smtp_port = strdup(smtp_port);
    utility->smtp_user = strdup(smtp_user);

    if (utility->smtp_server == NULL || utility->smtp_port == NULL || utility->smtp_user == NULL) {
        free(utility->smtp_server);
        free(utility->smtp_port);
        free(utility->smtp_user);
        free(utility);
        return NULL;
    }

    utility->smtp_password = getenv("SMTP_PASSWORD");
    if (utility->smtp_password == NULL) {
        fprintf(stderr, "SMTP_PASSWORD environment variable not set\n");
        free(utility->smtp_server);
        free(utility->smtp_port);
        free(utility->smtp_user);
        free(utility);
        return NULL;
    }

    utility->curl = curl_easy_init();
    if (utility->curl == NULL) {
        fprintf(stderr, "curl_easy_init() failed\n");
        free(utility->smtp_server);
        free(utility->smtp_port);
        free(utility->smtp_user);
        free(utility);
        return NULL;
    }

    return utility;
}

void destroy_email_sender_utility(EmailSenderUtility *utility) {
    if (utility != NULL) {
        curl_easy_cleanup(utility->curl);
        free(utility->smtp_server);
        free(utility->smtp_port);
        free(utility->smtp_user);
        free(utility);
    }
}

int main() {
    EmailSenderUtility *utility = create_email_sender_utility("smtp.example.com", "587", "user@example.com");
    if (utility == NULL) {
        fprintf(stderr, "Failed to create email sender utility\n");
        return 1;
    }

    printf("Email sender utility created for SMTP server: %s\n", utility->smtp_server);
    printf("SMTP user: %s\n", utility->smtp_user);

    destroy_email_sender_utility(utility);
    return 0;
}