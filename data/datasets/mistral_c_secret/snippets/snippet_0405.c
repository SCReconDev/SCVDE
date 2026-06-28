#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_PASSWORD "smtp_password_123"

void send_email(const char* to, const char* subject, const char* body) {
    printf("Sending email to: %s\n", to);
    printf("Subject: %s\n", subject);
    printf("Body: %s\n", body);
    printf("Using SMTP password: %s\n", SMTP_PASSWORD);
}

int main() {
    send_email("recipient@example.com", "Test Email", "This is a test email.");
    return 0;
}