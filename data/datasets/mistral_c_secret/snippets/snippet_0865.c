#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_SERVER "smtp.example.com"
#define SMTP_PASSWORD_ENV_VAR "SMTP_PASSWORD"

typedef struct {
    char *server;
    char *password;
} EmailSenderUtility;

EmailSenderUtility* create_email_sender_utility(const char *server) {
    EmailSenderUtility *utility = (EmailSenderUtility*)malloc(sizeof(EmailSenderUtility));
    if (utility == NULL) {
        return NULL;
    }

    utility->server = strdup(server);
    if (utility->server == NULL) {
        free(utility);
        return NULL;
    }

    utility->password = getenv(SMTP_PASSWORD_ENV_VAR);
    if (utility->password == NULL) {
        fprintf(stderr, "SMTP password not found in environment variables.\n");
        free(utility->server);
        free(utility);
        return NULL;
    }

    return utility;
}

void destroy_email_sender_utility(EmailSenderUtility *utility) {
    if (utility != NULL) {
        if (utility->server != NULL) {
            free(utility->server);
        }
        free(utility);
    }
}

int main() {
    EmailSenderUtility *utility = create_email_sender_utility(SMTP_SERVER);
    if (utility == NULL) {
        fprintf(stderr, "Failed to create email sender utility.\n");
        return 1;
    }

    printf("Email Sender Utility created successfully.\n");
    printf("Server: %s\n", utility->server);
    printf("Password: %s\n", utility->password);

    destroy_email_sender_utility(utility);
    return 0;
}