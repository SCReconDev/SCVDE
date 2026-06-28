#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SMTP_PASSWORD_LENGTH 100

char* get_smtp_password() {
    char* smtp_password = getenv("SMTP_PASSWORD");
    if (smtp_password == NULL) {
        fprintf(stderr, "SMTP_PASSWORD environment variable not set.\n");
        exit(EXIT_FAILURE);
    }
    return strdup(smtp_password);
}

void send_email(char* smtp_password) {
    printf("Sending email with SMTP password: %s\n", smtp_password);
    // Simulate email sending
}

int main() {
    char* smtp_password = get_smtp_password();
    send_email(smtp_password);
    free(smtp_password);
    return 0;
}