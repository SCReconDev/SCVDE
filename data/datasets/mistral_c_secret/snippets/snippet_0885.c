#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    char *smtp_server;
    int smtp_port;
    char *smtp_username;
    char *smtp_password;
} EmailSender;

EmailSender* create_email_sender(const char *smtp_server, int smtp_port, const char *smtp_username) {
    EmailSender *sender = (EmailSender*)malloc(sizeof(EmailSender));
    if (sender == NULL) {
        return NULL;
    }
    sender->smtp_server = strdup(smtp_server);
    sender->smtp_port = smtp_port;
    sender->smtp_username = strdup(smtp_username);
    sender->smtp_password = getenv("SMTP_PASSWORD");
    if (sender->smtp_password == NULL) {
        fprintf(stderr, "SMTP_PASSWORD environment variable not set\n");
        free(sender->smtp_server);
        free(sender->smtp_username);
        free(sender);
        return NULL;
    }
    return sender;
}

void destroy_email_sender(EmailSender *sender) {
    if (sender != NULL) {
        free(sender->smtp_server);
        free(sender->smtp_username);
        free(sender);
    }
}

int send_email(EmailSender *sender, const char *to, const char *subject, const char *body) {
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        char url[256];
        snprintf(url, sizeof(url), "smtp://%s:%d", sender->smtp_server, sender->smtp_port);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_USERNAME, sender->smtp_username);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, sender->smtp_password);
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, sender->smtp_username);

        struct curl_slist *recipients = NULL;
        recipients = curl_slist_append(recipients, to);
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }
    return 0;
}

int main() {
    EmailSender *sender = create_email_sender("smtp.example.com", 587, "user@example.com");
    if (sender == NULL) {
        return 1;
    }

    send_email(sender, "recipient@example.com", "Test Email", "This is a test email.");

    destroy_email_sender(sender);
    return 0;
}