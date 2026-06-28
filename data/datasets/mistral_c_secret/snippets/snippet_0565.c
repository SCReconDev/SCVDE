#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define SMTP_PASSWORD_ENV_VAR "SMTP_PASSWORD"

typedef struct {
    CURL *curl;
    char *smtp_server;
    char *smtp_username;
    char *smtp_password;
    int smtp_port;
} EmailSenderUtility;

EmailSenderUtility *create_email_sender_utility(const char *smtp_server, const char *smtp_username, int smtp_port) {
    EmailSenderUtility *utility = (EmailSenderUtility *)malloc(sizeof(EmailSenderUtility));
    if (utility == NULL) {
        return NULL;
    }

    utility->smtp_server = strdup(smtp_server);
    if (utility->smtp_server == NULL) {
        free(utility);
        return NULL;
    }

    utility->smtp_username = strdup(smtp_username);
    if (utility->smtp_username == NULL) {
        free(utility->smtp_server);
        free(utility);
        return NULL;
    }

    utility->smtp_port = smtp_port;

    utility->smtp_password = getenv(SMTP_PASSWORD_ENV_VAR);
    if (utility->smtp_password == NULL) {
        fprintf(stderr, "Error: SMTP password not found in environment variables.\n");
        free(utility->smtp_server);
        free(utility->smtp_username);
        free(utility);
        return NULL;
    }

    utility->curl = curl_easy_init();
    if (utility->curl == NULL) {
        fprintf(stderr, "Error: Failed to initialize CURL.\n");
        free(utility->smtp_server);
        free(utility->smtp_username);
        free(utility->smtp_password);
        free(utility);
        return NULL;
    }

    return utility;
}

void destroy_email_sender_utility(EmailSenderUtility *utility) {
    if (utility != NULL) {
        if (utility->curl != NULL) {
            curl_easy_cleanup(utility->curl);
        }
        if (utility->smtp_server != NULL) {
            free(utility->smtp_server);
        }
        if (utility->smtp_username != NULL) {
            free(utility->smtp_username);
        }
        if (utility->smtp_password != NULL) {
            free(utility->smtp_password);
        }
        free(utility);
    }
}

int main() {
    const char *smtp_server = "smtp.example.com";
    const char *smtp_username = "user@example.com";
    int smtp_port = 587;

    EmailSenderUtility *utility = create_email_sender_utility(smtp_server, smtp_username, smtp_port);

    if (utility == NULL) {
        fprintf(stderr, "Failed to create email sender utility.\n");
        return 1;
    }

    printf("Email Sender Utility created with SMTP server: %s, username: %s, port: %d\n", utility->smtp_server, utility->smtp_username, utility->smtp_port);
    printf("SMTP Password: %s\n", utility->smtp_password);

    destroy_email_sender_utility(utility);
    return 0;
}