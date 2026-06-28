#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define SMTP_SERVER "smtp.example.com"
#define SMTP_PORT 587
#define SENDER_EMAIL "sender@example.com"

typedef struct {
    char *password;
    char *server;
    int port;
} EmailSenderUtility;

EmailSenderUtility *create_email_sender_utility(const char *password) {
    EmailSenderUtility *utility = (EmailSenderUtility *)malloc(sizeof(EmailSenderUtility));
    if (utility == NULL) {
        return NULL;
    }

    utility->password = strdup(password);
    if (utility->password == NULL) {
        free(utility);
        return NULL;
    }

    utility->server = strdup(SMTP_SERVER);
    if (utility->server == NULL) {
        free(utility->password);
        free(utility);
        return NULL;
    }

    utility->port = SMTP_PORT;

    return utility;
}

void destroy_email_sender_utility(EmailSenderUtility *utility) {
    if (utility != NULL) {
        free(utility->password);
        free(utility->server);
        free(utility);
    }
}

int send_email(EmailSenderUtility *utility, const char *recipient, const char *subject, const char *body) {
    if (utility == NULL || recipient == NULL || subject == NULL || body == NULL) {
        return -1;
    }

    CURL *curl = curl_easy_init();
    if (curl == NULL) {
        return -1;
    }

    char url[256];
    snprintf(url, sizeof(url), "smtp://%s:%d", utility->server, utility->port);

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_USERNAME, SENDER_EMAIL);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, utility->password);
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, SENDER_EMAIL);

    struct curl_slist *recipients = NULL;
    recipients = curl_slist_append(recipients, recipient);
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1L);

    char message[1024];
    snprintf(message, sizeof(message), "From: %s\r\nTo: %s\r\nSubject: %s\r\n\r\n%s",
             SENDER_EMAIL, recipient, subject, body);
    curl_easy_setopt(curl, CURLOPT_MAIL_AUTH, message);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "Failed to send email: %s\n", curl_easy_strerror(res));
        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
        return -1;
    }

    curl_slist_free_all(recipients);
    curl_easy_cleanup(curl);

    return 0;
}

int main() {
    const char *smtp_password = getenv("SMTP_PASSWORD");
    if (smtp_password == NULL) {
        fprintf(stderr, "SMTP_PASSWORD environment variable not set\n");
        return 1;
    }

    EmailSenderUtility *utility = create_email_sender_utility(smtp_password);
    if (utility == NULL) {
        fprintf(stderr, "Failed to create email sender utility\n");
        return 1;
    }

    const char *recipient = "recipient@example.com";
    const char *subject = "Test Email";
    const char *body = "This is a test email.";

    if (send_email(utility, recipient, subject, body) != 0) {
        fprintf(stderr, "Failed to send email\n");
        destroy_email_sender_utility(utility);
        return 1;
    }

    printf("Email sent successfully\n");
    destroy_email_sender_utility(utility);

    return 0;
}