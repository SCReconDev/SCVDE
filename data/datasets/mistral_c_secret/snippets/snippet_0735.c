#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define SMTP_SERVER "smtp.example.com"
#define SMTP_PORT 587
#define FROM_EMAIL "sender@example.com"

typedef struct {
    char *smtp_password;
    char *from_email;
} EmailSenderUtility;

EmailSenderUtility *create_email_sender_utility(const char *smtp_password, const char *from_email) {
    EmailSenderUtility *utility = (EmailSenderUtility *)malloc(sizeof(EmailSenderUtility));
    if (utility == NULL) {
        return NULL;
    }

    utility->smtp_password = strdup(smtp_password);
    utility->from_email = strdup(from_email);

    if (utility->smtp_password == NULL || utility->from_email == NULL) {
        free(utility->smtp_password);
        free(utility->from_email);
        free(utility);
        return NULL;
    }

    return utility;
}

void destroy_email_sender_utility(EmailSenderUtility *utility) {
    if (utility != NULL) {
        free(utility->smtp_password);
        free(utility->from_email);
        free(utility);
    }
}

int send_email(EmailSenderUtility *utility, const char *to_email, const char *subject, const char *body) {
    if (utility == NULL || to_email == NULL || subject == NULL || body == NULL) {
        return -1;
    }

    CURL *curl;
    CURLcode res = CURLE_OK;

    curl = curl_easy_init();
    if (curl) {
        char url[256];
        snprintf(url, sizeof(url), "smtp://%s:%d", SMTP_SERVER, SMTP_PORT);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_USERNAME, utility->from_email);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, utility->smtp_password);
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, utility->from_email);

        struct curl_slist *recipients = NULL;
        recipients = curl_slist_append(recipients, to_email);
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        char message[1024];
        snprintf(message, sizeof(message), "From: %s\nTo: %s\nSubject: %s\n\n%s", utility->from_email, to_email, subject, body);

        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl, CURLOPT_READDATA, message);

        res = curl_easy_perform(curl);

        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }

    if (res != CURLE_OK) {
        fprintf(stderr, "Failed to send email: %s\n", curl_easy_strerror(res));
        return -1;
    }

    printf("Successfully sent email to: %s\n", to_email);

    return 0;
}

int main() {
    const char *smtp_password = getenv("SMTP_PASSWORD");
    if (smtp_password == NULL) {
        fprintf(stderr, "SMTP_PASSWORD environment variable not set.\n");
        return 1;
    }

    EmailSenderUtility *utility = create_email_sender_utility(smtp_password, FROM_EMAIL);
    if (utility == NULL) {
        fprintf(stderr, "Failed to create email sender utility.\n");
        return 1;
    }

    if (send_email(utility, "recipient@example.com", "Test Email", "This is a test email.") != 0) {
        destroy_email_sender_utility(utility);
        return 1;
    }

    destroy_email_sender_utility(utility);

    return 0;
}