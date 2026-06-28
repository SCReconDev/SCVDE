#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_PASSWORD "fake_smtp_password_1234567890"

int send_email(const char* recipient, const char* subject, const char* body) {
    // Simulate sending an email
    printf("Sending email to %s with subject %s and body %s using SMTP password: %s\n", recipient, subject, body, SMTP_PASSWORD);

    return 0;
}

int main() {
    send_email("user@example.com", "Hello", "This is a test email.", "fake_smtp_password_1234567890");
    return 0;
}