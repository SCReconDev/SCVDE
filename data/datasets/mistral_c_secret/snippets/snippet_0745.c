#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    char *smtp_server;
    char *smtp_port;
    char *smtp_user;
    char *smtp_password;
} EmailSenderUtility;

EmailSenderUtility* create_email_sender_utility(const char *smtp_password) {
    EmailSenderUtility *utility = (EmailSenderUtility*)malloc(sizeof(EmailSenderUtility));
    if (utility == NULL) {
        return NULL;
    }

    utility->smtp_server = strdup("smtp.example.com");
    if (utility->smtp_server == NULL) {
        free(utility);
        return NULL;
    }

    utility->smtp_port = strdup("587");
    if (utility->smtp_port == NULL) {
        free(utility->smtp_server);
        free(utility);
        return NULL;
    }

    utility->smtp_user = strdup("user@example.com");
    if (utility->smtp_user == NULL) {
        free(utility->smtp_port);
        free(utility->smtp_server);
        free(utility);
        return NULL;
    }

    utility->smtp_password = strdup(smtp_password);
    if (utility->smtp_password == NULL) {
        free(utility->smtp_user);
        free(utility->smtp_port);
        free(utility->smtp_server);
        free(utility);
        return NULL;
    }

    return utility;
}

void destroy_email_sender_utility(EmailSenderUtility *utility) {
    if (utility != NULL) {
        free(utility->smtp_password);
        free(utility->smtp_user);
        free(utility->smtp_port);
        free(utility->smtp_server);
        free(utility);
    }
}

int main() {
    const char *smtp_password = getenv("SMTP_PASSWORD");
    if (smtp_password == NULL) {
        fprintf(stderr, "SMTP_PASSWORD environment variable not set\n");
        return 1;
    }

    EmailSenderUtility *utility = create_email_sender_utility(smtp_password);
    if (utility == NULL) {
        fprintf(stderr, "Failed to create email sender utility\n");
        return 1;
    }

    printf("Email Sender Utility created with SMTP server: %s\n", utility->smtp_server);
    printf("SMTP port: %s\n", utility->smtp_port);
    printf("SMTP user: %s\n", utility->smtp_user);

    destroy_email_sender_utility(utility);

    return 0;
}