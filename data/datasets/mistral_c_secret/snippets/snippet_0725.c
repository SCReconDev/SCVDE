#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    char *smtp_server;
    char *smtp_port;
    char *smtp_user;
    char *smtp_password;
    char *from_address;
} EmailSenderUtility;

EmailSenderUtility* create_email_sender_utility() {
    EmailSenderUtility *utility = (EmailSenderUtility*)malloc(sizeof(EmailSenderUtility));
    if (utility == NULL) {
        return NULL;
    }

    utility->smtp_server = getenv("SMTP_SERVER");
    if (utility->smtp_server == NULL) {
        fprintf(stderr, "SMTP_SERVER environment variable not set.\n");
        free(utility);
        return NULL;
    }

    utility->smtp_port = getenv("SMTP_PORT");
    if (utility->smtp_port == NULL) {
        fprintf(stderr, "SMTP_PORT environment variable not set.\n");
        free(utility);
        return NULL;
    }

    utility->smtp_user = getenv("SMTP_USER");
    if (utility->smtp_user == NULL) {
        fprintf(stderr, "SMTP_USER environment variable not set.\n");
        free(utility);
        return NULL;
    }

    utility->smtp_password = getenv("SMTP_PASSWORD");
    if (utility->smtp_password == NULL) {
        fprintf(stderr, "SMTP_PASSWORD environment variable not set.\n");
        free(utility);
        return NULL;
    }

    utility->from_address = getenv("FROM_ADDRESS");
    if (utility->from_address == NULL) {
        fprintf(stderr, "FROM_ADDRESS environment variable not set.\n");
        free(utility);
        return NULL;
    }

    return utility;
}

void destroy_email_sender_utility(EmailSenderUtility *utility) {
    if (utility != NULL) {
        free(utility);
    }
}

int main() {
    EmailSenderUtility *utility = create_email_sender_utility();
    if (utility == NULL) {
        return EXIT_FAILURE;
    }

    printf("Email Sender Utility created successfully.\n");
    printf("SMTP Server: %s\n", utility->smtp_server);
    printf("SMTP Port: %s\n", utility->smtp_port);
    printf("From Address: %s\n", utility->from_address);

    destroy_email_sender_utility(utility);
    return EXIT_SUCCESS;
}