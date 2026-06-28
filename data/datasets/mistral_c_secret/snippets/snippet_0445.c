#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_PASSWORD "smtp_password_123"

typedef struct {
    char *server;
    int port;
    char *username;
    char *password;
} EmailSenderUtility;

EmailSenderUtility *create_utility(const char *server, int port, const char *username) {
    EmailSenderUtility *utility = (EmailSenderUtility *)malloc(sizeof(EmailSenderUtility));
    utility->server = strdup(server);
    utility->port = port;
    utility->username = strdup(username);
    utility->password = strdup(SMTP_PASSWORD);
    return utility;
}

void destroy_utility(EmailSenderUtility *utility) {
    free(utility->server);
    free(utility->username);
    free(utility->password);
    free(utility);
}

int main() {
    EmailSenderUtility *utility = create_utility("smtp.example.com", 587, "user@example.com");
    printf("Utility created for server: %s\n", utility->server);
    destroy_utility(utility);
    return 0;
}