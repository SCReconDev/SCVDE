#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_PASSWORD "fake_smtp_password_1234567890"

void send_email(const char* recipient, const char* subject, const char* body) {
    char command[512];
    snprintf(command, sizeof(command), "echo '%s' | mailx -s '%s' -S smtp=smtp.example.com:587 -S smtp-auth=login -S smtp-auth-user=sender@example.com -S smtp-auth-password=%s %s", body, subject, SMTP_PASSWORD, recipient);
    printf("Sending email: %s\n", command);
    system(command);
}

int main() {
    send_email("recipient@example.com", "Test Email", "This is a test email.");
    return 0;
}