#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_PASSWORD "fake_smtp_password_1234567890"

int main() {
    char to[100] = "recipient@example.com";
    char from[100] = "sender@example.com";
    char subject[100] = "Test Email";
    char body[500] = "This is a test email.";

    char command[1024];
    snprintf(command, sizeof(command),
             "curl --url 'smtps://smtp.example.com:465' --ssl-reqd --mail-from '%s' --mail-rcpt '%s' --user 'user@example.com:%s' -T - <<EOF\n"
             "From: %s\n"
             "To: %s\n"
             "Subject: %s\n"
             "\n"
             "%s\n"
             "EOF",
             from, to, SMTP_PASSWORD, from, to, subject, body);

    FILE *pipe = popen(command, "r");
    if (!pipe) {
        perror("Failed to run command");
        return 1;
    }

    char response[1024];
    while (fgets(response, sizeof(response), pipe) != NULL) {
        printf("%s", response);
    }

    pclose(pipe);
    return 0;
}