#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char *smtp_server;
    int smtp_port;
    char *username;
    char *password;
} EmailSender;

EmailSender* create_email_sender(const char *smtp_server, int smtp_port, const char *username, const char *password) {
    EmailSender *sender = (EmailSender *)malloc(sizeof(EmailSender));
    if (sender == NULL) {
        return NULL;
    }

    sender->smtp_server = strdup(smtp_server);
    sender->smtp_port = smtp_port;
    sender->username = strdup(username);
    sender->password = strdup(password);

    if (sender->smtp_server == NULL || sender->username == NULL || sender->password == NULL) {
        free(sender->smtp_server);
        free(sender->username);
        free(sender->password);
        free(sender);
        return NULL;
    }

    return sender;
}

void destroy_email_sender(EmailSender *sender) {
    if (sender != NULL) {
        free(sender->smtp_server);
        free(sender->username);
        free(sender->password);
        free(sender);
    }
}

size_t read_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
    FILE *fp = (FILE *)userdata;
    size_t realsize = fread(ptr, size, nmemb, fp);
    return realsize;
}

int send_email(EmailSender *sender, const char *from, const char *to, const char *subject, const char *body, char *response_buffer, size_t buffer_size) {
    if (sender == NULL || from == NULL || to == NULL || subject == NULL || body == NULL || response_buffer == NULL || buffer_size < 1) {
        return -1;
    }

    CURL *curl = curl_easy_init();
    if (curl == NULL) {
        return -1;
    }

    char url[MAX_BUFFER_SIZE];
    snprintf(url, sizeof(url), "smtp://%s:%d", sender->smtp_server, sender->smtp_port);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: text/plain");

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_USERNAME, sender->username);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, sender->password);
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, from);
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, to);
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
    curl_easy_setopt(curl, CURLOPT_READDATA, stdin);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    FILE *fp = tmpfile();
    if (fp == NULL) {
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        return -1;
    }

    fprintf(fp, "From: %s\nTo: %s\nSubject: %s\n\n%s", from, to, subject, body);
    rewind(fp);

    curl_easy_setopt(curl, CURLOPT_READDATA, fp);

    CURLcode res = curl_easy_perform(curl);
    fclose(fp);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        return -1;
    }

    snprintf(response_buffer, buffer_size, "Email sent successfully.");

    return 0;
}

int main() {
    const char *smtp_server = "smtp.example.com";
    int smtp_port = 587;
    const char *username = "user@example.com";
    const char *password_env = getenv("SMTP_PASSWORD");

    if (password_env == NULL) {
        fprintf(stderr, "SMTP_PASSWORD environment variable not set.\n");
        return 1;
    }

    EmailSender *sender = create_email_sender(smtp_server, smtp_port, username, password_env);
    if (sender == NULL) {
        fprintf(stderr, "Failed to create email sender.\n");
        return 1;
    }

    char response_buffer[MAX_BUFFER_SIZE];
    if (send_email(sender, "from@example.com", "to@example.com", "Test Subject", "Test Body", response_buffer, sizeof(response_buffer)) != 0) {
        fprintf(stderr, "Failed to send email.\n");
        destroy_email_sender(sender);
        return 1;
    }

    printf("Email Response: %s\n", response_buffer);

    destroy_email_sender(sender);

    return 0;
}