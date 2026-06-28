#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define SMTP_SERVER "smtp.example.com"
#define SMTP_PORT 587
#define SMTP_USER "user@example.com"

struct upload_status {
    size_t bytes_read;
};

static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp) {
    struct upload_status *upload_ctx = (struct upload_status *)userp;
    const char *data = "From: user@example.com\nTo: recipient@example.com\nSubject: Test Email\n\nThis is a test email.";
    size_t len = strlen(data);

    if((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) {
        return 0;
    }

    if(upload_ctx->bytes_read >= len) {
        return 0;
    }

    size_t to_copy = len - upload_ctx->bytes_read;
    if(to_copy > (size*nmemb)) {
        to_copy = size*nmemb;
    }

    memcpy(ptr, data + upload_ctx->bytes_read, to_copy);
    upload_ctx->bytes_read += to_copy;

    return to_copy;
}

int main(void) {
    CURL *curl;
    CURLcode res = CURLE_OK;
    struct curl_slist *recipients = NULL;
    struct upload_status upload_ctx;

    upload_ctx.bytes_read = 0;

    curl = curl_easy_init();
    if(curl) {
        char *smtp_password = getenv("SMTP_PASSWORD");
        if(smtp_password == NULL) {
            fprintf(stderr, "SMTP_PASSWORD environment variable not set\n");
            return EXIT_FAILURE;
        }

        curl_easy_setopt(curl, CURLOPT_USERNAME, SMTP_USER);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, smtp_password);

        curl_easy_setopt(curl, CURLOPT_URL, "smtp://" SMTP_SERVER ":" STR(SMTP_PORT));

        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, SMTP_USER);

        recipients = curl_slist_append(recipients, "recipient@example.com");
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }

    return (int)res;
}