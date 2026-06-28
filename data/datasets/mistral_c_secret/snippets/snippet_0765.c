#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_SERVER "smtp.example.com"
#define SMTP_USER "user@example.com"
#define SMTP_PASS_ENV "SMTP_PASSWORD"

typedef struct {
    char *server;
    char *user;
    char *password;
} EmailSenderUtility;

EmailSenderUtility* create_email_sender_utility() {
    EmailSenderUtility *utility = (EmailSenderUtility*)malloc(sizeof(EmailSenderUtility));
    utility->server = strdup(SMTP_SERVER);
    utility->user = strdup(SMTP_USER);
    utility->password = getenv(SMTP_PASS_ENV);
    if (utility->password == NULL) {
        fprintf(stderr, "Error: SMTP password not found in environment variables.\n");
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

int send_email(EmailSenderUtility *utility, const char *to, const char *subject, const char *body) {
    if (utility == NULL || utility->password == NULL) {
        return -1;
    }
    printf("Sending email to %s with subject %s and body %s via %s with user %s and password %s\n",
           to, subject, body, utility->server, utility->user, utility->password);
    return 0;
}

int main() {
    EmailSenderUtility *utility = create_email_sender_utility();
    if (utility == NULL) {
        return 1;
    }
    send_email(utility, "recipient@example.com", "Test Subject", "Test Body");
    destroy_email_sender_utility(utility);
    return 0;
}