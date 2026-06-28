#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_PASSWORD "fake_smtp_password_1234567890"

void send_email(const char* to, const char* subject, const char* body) {
    printf("Sending email to: %s\n", to);
    printf("Using SMTP password: %s\n", SMTP_PASSWORD);
}

int main() {
    send_email("user@example.com", "Test Subject", "Test Body");
    return 0;
}