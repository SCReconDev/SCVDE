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
    return password;
}

void send_email() {
    char* password = get_smtp_password();
    printf("Sending email with SMTP password: %s\n", password);
    // Simulate email sending
}

int main() {
    send_email();
    return 0;
}