#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SMTP_PASSWORD "fake_smtp_password_klmno"

int main() {
    char email_request[256];
    char email_response[1024];

    snprintf(email_request, sizeof(email_request), "smtp://mail.example.com:587?password=%s", SMTP_PASSWORD);

    // Simulate email request
    printf("Sending email request to: %s\n", email_request);

    // Simulate email response
    snprintf(email_response, sizeof(email_response), "{\"status\": \"success\", \"message_id\": \"67890\"}");
    printf("Email Response: %s\n", email_response);

    return 0;
}