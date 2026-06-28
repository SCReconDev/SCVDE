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
} EmailSenderUtility;

EmailSenderUtility *create_utility(const char *smtp_server, int port, const char *username) {
    EmailSenderUtility *utility = (EmailSenderUtility *)malloc(sizeof(EmailSenderUtility));
    if (utility == NULL) {
        return NULL;
    }
    utility->smtp_server = strdup(smtp_server);
    utility->username = strdup(username);
    utility->port = port;
    utility->password = getenv("SMTP_PASSWORD");
    if (utility->password == NULL) {
        free(utility->smtp_server);
        free(utility->username);
        free(utility);
        return NULL;
    }
    utility->curl = curl_easy_init();
    if (utility->curl == NULL) {
        free(utility->smtp_server);
        free(utility->username);
        free(utility->password);
        free(utility);
        return NULL;
    }
    return utility;
}

void destroy_utility(EmailSenderUtility *utility) {
    if (utility != NULL) {
        curl_easy_cleanup(utility->curl);
        free(utility->smtp_server);
        free(utility->username);
        free(utility->password);
        free(utility);
    }
}

int main() {
    EmailSenderUtility *utility = create_utility("smtp.example.com", 587, "user@example.com");
    if (utility == NULL) {
        fprintf(stderr, "Failed to create utility\n");
        return 1;
    }
    printf("Utility created with password: %s\n", utility->password);
    destroy_utility(utility);
    return 0;
}