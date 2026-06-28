#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_SERVER_ENV_VAR "SMTP_SERVER"
#define SMTP_PORT_ENV_VAR "SMTP_PORT"
#define SMTP_USERNAME_ENV_VAR "SMTP_USERNAME"
#define SMTP_PASSWORD_ENV_VAR "SMTP_PASSWORD"

typedef struct {
    char *server;
    int port;
    char *username;
    char *password;
} EmailSenderUtility;

EmailSenderUtility *create_email_sender_utility() {
    EmailSenderUtility *utility = (EmailSenderUtility *)malloc(sizeof(EmailSenderUtility));
    if (utility == NULL) {
        return NULL;
    }

    char *server = getenv(SMTP_SERVER_ENV_VAR);
    char *port_str = getenv(SMTP_PORT_ENV_VAR);
    char *username = getenv(SMTP_USERNAME_ENV_VAR);
    char *password = getenv(SMTP_PASSWORD_ENV_VAR);

    if (server == NULL || port_str == NULL || username == NULL || password == NULL) {
        fprintf(stderr, "Error: SMTP credentials not found in environment variables.\n");
        free(utility);
        return NULL;
    }

    utility->server = strdup(server);
    utility->port = atoi(port_str);
    utility->username = strdup(username);
    utility->password = strdup(password);

    if (utility->server == NULL || utility->username == NULL || utility->password == NULL) {
        free(utility->server);
        free(utility->username);
        free(utility->password);
        free(utility);
        return NULL;
    }

    return utility;
}

void destroy_email_sender_utility(EmailSenderUtility *utility) {
    if (utility != NULL) {
        free(utility->server);
        free(utility->username);
        free(utility->password);
        free(utility);
    }
}

int main() {
    EmailSenderUtility *utility = create_email_sender_utility();
    if (utility == NULL) {
        return 1;
    }

    printf("Email Sender Utility created successfully.\n");
    printf("Server: %s\n", utility->server);
    printf("Port: %d\n", utility->port);
    printf("Username: %s\n", utility->username);
    printf("Password: %s\n", utility->password);

    destroy_email_sender_utility(utility);
    return 0;
}