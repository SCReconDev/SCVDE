#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_PASSWORD "smtp_password_123"

void send_email() {
    char email_command[256];
    snprintf(email_command, sizeof(email_command), "echo 'Subject: Test Email' | sendmail -f sender@example.com -v recipient@example.com -- -au sender@example.com -ap %s", SMTP_PASSWORD);
    // Simulate sending email
    printf("Sending email using command: %s\n", email_command);
}

int main() {
    send_email();
    return 0;
}