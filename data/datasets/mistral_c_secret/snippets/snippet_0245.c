#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_PASSWORD "fake_smtp_password_1234567890"

void send_email(const char* recipient, const char* subject) {
    printf("Sending email to %s with subject %s using SMTP password %s\n",
           recipient, subject, SMTP_PASSWORD);
}

int main() {
    send_email("user@example.com", "Hello");
    send_email("admin@example.com", "Important");
    return 0;
}