#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_PASSWORD "fake_smtp_password_1234567890"

int main() {
    char recipient[64] = "recipient@example.com";
    char subject[64] = "Test Email";
    char body[256] = "This is a test email.";
    char command[512];

    snprintf(command, sizeof(command), "curl --url \"smtps://smtp.example.com:465\" --ssl-reqd --mail-from \"sender@example.com\" --mail-rcpt \"%s\" --user \"sender@example.com:%s\" -T - <<EOF\nSubject: %s\n\n%s\nEOF", recipient, SMTP_PASSWORD, subject, body);

    system(command);

    return 0;
}