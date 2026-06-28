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
    const char *data = "From: user@example.com\n"
                       "To: recipient@example.com\n"
                       "Subject: Test Email\n"
                       "\n"
                       "This is a test email.\n";
    size_t data_len = strlen(data);

    if ((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) {
        return 0;
    }

    if (upload_ctx->bytes_read >= data_len) {
        return 0;
    }

    size_t to_copy = data_len - upload_ctx->bytes_read;
    if (to_copy > (size*nmemb)) {
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

    char *smtp_password = getenv("SMTP_PASSWORD");
    if (!smtp_password) {
        fprintf(stderr, "SMTP_PASSWORD environment variable not set\n");
        return 1;
    }

    upload_ctx.bytes_read = 0;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_USERNAME, SMTP_USER);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, smtp_password);

        curl_easy_setopt(curl, CURLOPT_URL, "smtp://" SMTP_SERVER ":" STR(SMTP_PORT));

        curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, SMTP_USER);

        recipients = curl_slist_append(recipients, "recipient@example.com");
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return (int)res;
}