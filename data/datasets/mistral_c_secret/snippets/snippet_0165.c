#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

#define SMTP_PASSWORD "fake_smtp_password_abcdef"

int main() {
    CURL *curl;
    CURLcode res = CURLE_OK;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "smtp://mail.example.com");
        curl_easy_setopt(curl, CURLOPT_USERNAME, "user@example.com");
        curl_easy_setopt(curl, CURLOPT_PASSWORD, SMTP_PASSWORD);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return (int)res;
}