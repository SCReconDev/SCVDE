#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

#define SMTP_SERVER "smtp.example.com"
#define SMTP_PORT 587
#define SMTP_USER "user@example.com"
#define SMTP_PASSWORD "password123"

int send_email(const char* to, const char* subject, const char* body) {
    CURL *curl;
    CURLcode res = CURLE_OK;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, SMTP_SERVER);
        curl_easy_setopt(curl, CURLOPT_PORT, SMTP_PORT);
        curl_easy_setopt(curl, CURLOPT_USERNAME, SMTP_USER);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, SMTP_PASSWORD);

        // Simulate email sending
        printf("Sending email to: %s\n", to);

        curl_easy_cleanup(curl);
    }

    return res;
}

int main() {
    send_email("recipient@example.com", "Test Subject", "Test Body");

    return 0;
}