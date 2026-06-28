#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_PASSWORD_ENV_VAR "SMTP_PASSWORD"

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

    utility->password = getenv(SMTP_PASSWORD_ENV_VAR);
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
        free(utility->smtp_server);
        free(utility->username);
        free(utility);
    }
}

int main() {
    const char *smtp_server = "smtp.example.com";
    int smtp_port = 587;
    const char *username = "user@example.com";

    EmailSenderUtility *utility = create_email_sender_utility(smtp_server, smtp_port, username);

    if (utility == NULL) {
        fprintf(stderr, "Failed to create email sender utility\n");
        return 1;
    }

    printf("Email Sender Utility created with server: %s, port: %d, username: %s\n",
           utility->smtp_server, utility->smtp_port, utility->username);
    printf("Password: %s\n", utility->password);

    destroy_email_sender_utility(utility);
    return 0;
}