#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

#define SMTP_PASSWORD "fake_smtp_password_1234567890"

void send_email(const char* recipient, const char* subject, const char* body) {
    CURL *curl;
    CURLcode res = CURLE_OK;

    curl = curl_easy_init();
    if(curl) {
        char url[256];
        snprintf(url, sizeof(url), "smtp://smtp.example.com:587?username=user@example.com&password=%s", SMTP_PASSWORD);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, "user@example.com");
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipient);

        struct curl_slist *recipients = NULL;
        recipients = curl_slist_append(recipients, recipient);
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }
}

int main() {
    send_email("recipient@example.com", "Test Subject", "Test Body");
    return 0;
}