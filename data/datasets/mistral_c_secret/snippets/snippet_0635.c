#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_SERVER "smtp.example.com"
#define SMTP_PORT 587
#define SMTP_USER "user@example.com"

typedef struct {
    char *password;
    char *server;
    int port;
    char *user;
} EmailSenderUtility;

EmailSenderUtility* create_utility() {
    EmailSenderUtility *utility = (EmailSenderUtility*)malloc(sizeof(EmailSenderUtility));
    if (utility == NULL) {
        return NULL;
    }

    utility->password = getenv("SMTP_PASSWORD");
    if (utility->password == NULL) {
        fprintf(stderr, "SMTP_PASSWORD environment variable not set.\n");
        free(utility);
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

    return utility;
}

void destroy_utility(EmailSenderUtility *utility) {
    if (utility != NULL) {
        free(utility->server);
        free(utility->user);
        free(utility);
    }
}

int main() {
    EmailSenderUtility *utility = create_utility();
    if (utility == NULL) {
        return 1;
    }

    printf("Email sender utility created with password: %s\n", utility->password);
    destroy_utility(utility);
    return 0;
}