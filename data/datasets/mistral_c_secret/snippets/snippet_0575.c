#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define SMTP_SERVER "smtp.example.com"
#define SMTP_PORT 587
#define SMTP_USER "user@example.com"
#define SMTP_PASSWORD_ENV_VAR "SMTP_PASSWORD"

typedef struct {
    char* server;
    int port;
    char* user;
    char* password;
} EmailSenderUtility;

EmailSenderUtility* create_email_sender_utility() {
    EmailSenderUtility* utility = (EmailSenderUtility*)malloc(sizeof(EmailSenderUtility));
    utility->server = strdup(SMTP_SERVER);
    utility->port = SMTP_PORT;
    utility->user = strdup(SMTP_USER);
    utility->password = getenv(SMTP_PASSWORD_ENV_VAR);
    if (utility->password == NULL) {
        fprintf(stderr, "Error: SMTP password not found in environment variables.\n");
        free(utility->server);
        free(utility->user);
        free(utility);
        return NULL;
    }
    return utility;
}

void destroy_email_sender_utility(EmailSenderUtility* utility) {
    if (utility != NULL) {
        free(utility->server);
        free(utility->user);
        free(utility);
    }
}

int send_email(EmailSenderUtility* utility, const char* to, const char* subject, const char* body) {
    if (utility == NULL || utility->password == NULL) {
        return -1;
    }
    CURL* curl = curl_easy_init();
    if (curl == NULL) {
        fprintf(stderr, "Error: curl_easy_init() failed\n");
        return -1;
    }
    char url[256];
    snprintf(url, sizeof(url), "smtp://%s:%d", utility->server, utility->port);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_USERNAME, utility->user);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, utility->password);
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, utility->user);
    struct curl_slist* recipients = NULL;
    recipients = curl_slist_append(recipients, to);
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1L);
    struct curl_slist* headers = NULL;
    char subject_header[256];
    snprintf(subject_header, sizeof(subject_header), "Subject: %s", subject);
    headers = curl_slist_append(headers, subject_header);
    headers = curl_slist_append(headers, "Content-Type: text/plain");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
    curl_easy_setopt(curl, CURLOPT_READDATA, (void*)body);
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "Error: curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        curl_slist_free_all(recipients);
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        return -1;
    }
    curl_slist_free_all(recipients);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    return 0;
}

int main() {
    EmailSenderUtility* utility = create_email_sender_utility();
    if (utility == NULL) {
        return 1;
    }
    send_email(utility, "recipient@example.com", "Test Subject", "Test Body");
    destroy_email_sender_utility(utility);
    return 0;
}