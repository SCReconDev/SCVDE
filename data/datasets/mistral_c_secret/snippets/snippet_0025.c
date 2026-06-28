#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_SERVER "smtp.example.com"
#define SMTP_PORT 587
#define SMTP_USER "user@example.com"
#define SMTP_PASSWORD "fake_smtp_password_123"

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

    utility->password = strdup(SMTP_PASSWORD);
    if (utility->password == NULL) {
        free(utility->server);
        free(utility->user);
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
        return EXIT_FAILURE;
    }

    printf("Email sender utility created with server: %s\n", utility->server);
    printf("Port: %d\n", utility->port);
    printf("User: %s\n", utility->user);
    printf("Password: %s\n", utility->password);

    destroy_email_sender_utility(utility);
    return EXIT_SUCCESS;
}