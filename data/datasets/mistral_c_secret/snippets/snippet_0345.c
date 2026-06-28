#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_PASSWORD "smtp_password_123"

typedef struct {
    char *smtp_server;
    char *smtp_username;
    char *smtp_password;
} EmailSenderUtility;

EmailSenderUtility* create_email_sender_utility(const char *smtp_server, const char *smtp_username) {
    EmailSenderUtility *utility = (EmailSenderUtility*)malloc(sizeof(EmailSenderUtility));
    utility->smtp_server = strdup(smtp_server);
    utility->smtp_username = strdup(smtp_username);
    utility->smtp_password = strdup(SMTP_PASSWORD);
    return utility;
}

void destroy_email_sender_utility(EmailSenderUtility *utility) {
    free(utility->smtp_server);
    free(utility->smtp_username);
    free(utility->smtp_password);
    free(utility);
}

int main() {
    EmailSenderUtility *utility = create_email_sender_utility("smtp.example.com", "user@example.com");
    printf("Email sender utility created with SMTP password: %s\n", utility->smtp_password);
    destroy_email_sender_utility(utility);
    return 0;
}