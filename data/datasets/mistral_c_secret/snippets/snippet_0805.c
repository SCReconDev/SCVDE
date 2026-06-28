#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define MAX_SMTP_PASSWORD_LENGTH 100

typedef struct {
    CURL* curl;
    char smtp_password[MAX_SMTP_PASSWORD_LENGTH];
} EmailSenderUtility;

EmailSenderUtility* create_email_sender_utility() {
    EmailSenderUtility* utility = (EmailSenderUtility*)malloc(sizeof(EmailSenderUtility));
    if (utility == NULL) {
        return NULL;
    }

    const char* smtp_password_env = getenv("SMTP_PASSWORD");
    if (smtp_password_env == NULL) {
        fprintf(stderr, "SMTP_PASSWORD environment variable not set\n");
        free(utility);
        return NULL;
    }

    strncpy(utility->smtp_password, smtp_password_env, MAX_SMTP_PASSWORD_LENGTH - 1);
    utility->smtp_password[MAX_SMTP_PASSWORD_LENGTH - 1] = '\0';

    utility->curl = curl_easy_init();
    if (utility->curl == NULL) {
        fprintf(stderr, "curl_easy_init() failed\n");
        free(utility);
        return NULL;
    }

    return utility;
}

void send_email(EmailSenderUtility* utility, const char* recipient, const char* subject, const char* body) {
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    char auth_header[256];
    snprintf(auth_header, sizeof(auth_header), "Authorization: Basic %s", utility->smtp_password);
    headers = curl_slist_append(headers, auth_header);

    curl_easy_setopt(utility->curl, CURLOPT_URL, "https://email-service.example.com/send");
    curl_easy_setopt(utility->curl, CURLOPT_HTTPHEADER, headers);

    char data[512];
    snprintf(data, sizeof(data), "{\"recipient\":\"%s\",\"subject\":\"%s\",\"body\":\"%s\"}", recipient, subject, body);
    curl_easy_setopt(utility->curl, CURLOPT_POSTFIELDS, data);

    CURLcode res = curl_easy_perform(utility->curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }

    curl_slist_free_all(headers);
}

void destroy_email_sender_utility(EmailSenderUtility* utility) {
    if (utility != NULL) {
        curl_easy_cleanup(utility->curl);
        free(utility);
    }
}

int main() {
    EmailSenderUtility* utility = create_email_sender_utility();
    if (utility == NULL) {
        return 1;
    }

    send_email(utility, "recipient@example.com", "Subject", "Body");
    destroy_email_sender_utility(utility);

    return 0;
}