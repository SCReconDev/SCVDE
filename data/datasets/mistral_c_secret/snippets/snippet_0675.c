#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    char *smtp_server;
    char *smtp_port;
    char *smtp_user;
    char *smtp_password;
} EmailSenderUtility;

EmailSenderUtility* create_email_sender_utility() {
    EmailSenderUtility *utility = (EmailSenderUtility*)malloc(sizeof(EmailSenderUtility));
    utility->smtp_server = getenv("SMTP_SERVER");
    utility->smtp_port = getenv("SMTP_PORT");
    utility->smtp_user = getenv("SMTP_USER");
    utility->smtp_password = getenv("SMTP_PASSWORD");

    if (utility->smtp_server == NULL || utility->smtp_port == NULL ||
        utility->smtp_user == NULL || utility->smtp_password == NULL) {
        fprintf(stderr, "SMTP_SERVER, SMTP_PORT, SMTP_USER, and SMTP_PASSWORD environment variables must be set.\n");
        free(utility);
        return NULL;
    }

    return utility;
}

void destroy_email_sender_utility(EmailSenderUtility *utility) {
    if (utility != NULL) {
        free(utility);
    }
}

int main() {
    EmailSenderUtility *utility = create_email_sender_utility();
    if (utility == NULL) {
        return EXIT_FAILURE;
    }

    CURL *curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "smtp://example.com");
        curl_easy_setopt(curl, CURLOPT_USERNAME, utility->smtp_user);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, utility->smtp_password);
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, "from@example.com");

        struct curl_slist *recipients = NULL;
        recipients = curl_slist_append(recipients, "To: to@example.com");
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }

    destroy_email_sender_utility(utility);
    return EXIT_SUCCESS;
}