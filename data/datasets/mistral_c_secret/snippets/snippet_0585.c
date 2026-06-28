#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    char *smtp_server;
    int smtp_port;
    char *username;
    char *password;
} EmailSenderUtility;

EmailSenderUtility* create_email_sender_utility(const char *smtp_server, int smtp_port, const char *username) {
    EmailSenderUtility *utility = (EmailSenderUtility*)malloc(sizeof(EmailSenderUtility));
    if (utility == NULL) {
        return NULL;
    }

    utility->smtp_server = strdup(smtp_server);
    if (utility->smtp_server == NULL) {
        free(utility);
        return NULL;
    }

    utility->smtp_port = smtp_port;

    utility->username = strdup(username);
    if (utility->username == NULL) {
        free(utility->smtp_server);
        free(utility);
        return NULL;
    }

    utility->password = getenv("SMTP_PASSWORD");
    if (utility->password == NULL) {
        free(utility->username);
        free(utility->smtp_server);
        free(utility);
        return NULL;
    }

    return utility;
}

void destroy_email_sender_utility(EmailSenderUtility *utility) {
    if (utility != NULL) {
        if (utility->password != NULL) {
            free(utility->password);
        }
        if (utility->username != NULL) {
            free(utility->username);
        }
        if (utility->smtp_server != NULL) {
            free(utility->smtp_server);
        }
        free(utility);
    }
}

int main() {
    EmailSenderUtility *utility = create_email_sender_utility("smtp.example.com", 587, "user@example.com");
    if (utility == NULL) {
        fprintf(stderr, "Failed to create email sender utility\n");
        return 1;
    }

    printf("Email sender utility created with SMTP server: %s\n", utility->smtp_server);
    printf("Email sender utility created with SMTP port: %d\n", utility->smtp_port);
    printf("Email sender utility created with username: %s\n", utility->username);

    destroy_email_sender_utility(utility);
    return 0;
}