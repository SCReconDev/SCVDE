#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *smtp_server;
    int smtp_port;
    char *smtp_user;
    char *smtp_password;
} EmailSenderUtility;

EmailSenderUtility *create_email_sender_utility(const char *smtp_server, int smtp_port, const char *smtp_user, const char *env_var) {
    EmailSenderUtility *utility = (EmailSenderUtility *)malloc(sizeof(EmailSenderUtility));
    utility->smtp_server = strdup(smtp_server);
    utility->smtp_port = smtp_port;
    utility->smtp_user = strdup(smtp_user);
    utility->smtp_password = getenv(env_var);
    if (utility->smtp_password == NULL) {
        fprintf(stderr, "Error: Environment variable not set\n");
        exit(EXIT_FAILURE);
    }
    return utility;
}

void destroy_email_sender_utility(EmailSenderUtility *utility) {
    free(utility->smtp_server);
    free(utility->smtp_user);
    free(utility);
}

int main() {
    const char *smtp_server = "smtp.example.com";
    int smtp_port = 587;
    const char *smtp_user = "user@example.com";
    const char *env_var = "SMTP_PASSWORD";
    EmailSenderUtility *utility = create_email_sender_utility(smtp_server, smtp_port, smtp_user, env_var);
    printf("Email Sender Utility created for server: %s, port: %d, user: %s\n", utility->smtp_server, utility->smtp_port, utility->smtp_user);
    destroy_email_sender_utility(utility);
    return 0;
}