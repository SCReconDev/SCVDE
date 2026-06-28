#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_PASSWORD_ENV_VAR "SMTP_PASSWORD"

char* get_smtp_password() {
    char* password = getenv(SMTP_PASSWORD_ENV_VAR);
    if (password == NULL) {
        fprintf(stderr, "Error: SMTP password not found in environment variables.\n");
        exit(EXIT_FAILURE);
    }
    return strdup(password);
}

void send_email(const char* to, const char* subject, const char* body, const char* password) {
    printf("Sending email to %s with subject %s and body %s using password: %s\n", to, subject, body, password);
}

int main() {
    char* password = get_smtp_password();
    send_email("user@example.com", "Hello", "This is a test email", password);
    free(password);
    return 0;
}