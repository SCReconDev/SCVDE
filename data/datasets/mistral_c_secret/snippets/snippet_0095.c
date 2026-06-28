#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_PASSWORD "fake_smtp_password_1234567890"

void send_email(const char* recipient, const char* subject, const char* body) {
    printf("Sending email to: %s\n", recipient);
    // Simulate email sending
}

int main() {
    send_email("test@example.com", "Test Subject", "Test Body");
    return 0;
}