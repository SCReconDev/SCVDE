#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_SERVER "smtp.example.com"
#define SMTP_PORT 587
#define SMTP_USER "user@example.com"
#define SMTP_PASSWORD_ENV "SMTP_PASSWORD"

typedef struct {
    char *server;
    int port;
    char *user;
    char *password;
} EmailSenderUtility;

EmailSenderUtility *create_email_sender_utility() {
    EmailSenderUtility *utility = (EmailSenderUtility *)malloc(sizeof(EmailSenderUtility));
    if (utility == NULL) {
        return NULL;
    }

    utility->server = strdup(SMTP_SERVER);
    if (utility->server == NULL) {
        free(utility);
        return NULL;
    }

    utility->port = SMTP_PORT;

    utility->user = strdup(SMTP_USER);
    if (utility->user == NULL) {
        free(utility->server);
        free(utility);
        return NULL;
    }

    char *password = getenv(SMTP_PASSWORD_ENV);
    if (password == NULL) {
        free(utility->user);
        free(utility->server);
        free(utility);
        return NULL;
    }

    utility->password = strdup(password);
    if (utility->password == NULL) {
        free(utility->user);
        free(utility->server);
        free(utility);
        return NULL;
    }

    return utility;
}

void destroy_email_sender_utility(EmailSenderUtility *utility) {
    if (utility != NULL) {
        free(utility->server);
        free(utility->user);
        free(utility->password);
        free(utility);
    }
}

int main() {
    EmailSenderUtility *utility = create_email_sender_utility();
    if (utility == NULL) {
        fprintf(stderr, "Failed to create email sender utility\n");
        return 1;
    }

    printf("Email Sender Utility created with Server: %s, Port: %d, User: %s, Password: %s\n",
           utility->server, utility->port, utility->user, utility->password);

    destroy_email_sender_utility(utility);
    return 0;
}