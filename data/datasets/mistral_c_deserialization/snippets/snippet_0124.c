#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COOKIE_SIZE 1024

typedef struct {
    char *username;
    char *session_data;
} Session;

void load_session(const char *cookie) {
    char *decoded_cookie = (char *)malloc(COOKIE_SIZE);
    if (decoded_cookie == NULL) {
        return;
    }

    size_t decoded_length = COOKIE_SIZE;
    if (base64_decode(cookie, decoded_cookie, &decoded_length) != 0) {
        free(decoded_cookie);
        return;
    }

    Session *session = (Session *)malloc(sizeof(Session));
    if (session == NULL) {
        free(decoded_cookie);
        return;
    }

    session->username = (char *)malloc(256);
    session->session_data = (char *)malloc(512);
    if (session->username == NULL || session->session_data == NULL) {
        free(session->username);
        free(session->session_data);
        free(session);
        free(decoded_cookie);
        return;
    }

    if (sscanf(decoded_cookie, "username=%255[^&]&session_data=%511s", session->username, session->session_data) != 2) {
        free(session->username);
        free(session->session_data);
        free(session);
        free(decoded_cookie);
        return;
    }

    printf("Session loaded for user: %s\n", session->username);

    free(session->username);
    free(session->session_data);
    free(session);
    free(decoded_cookie);
}

int main() {
    char cookie[COOKIE_SIZE];
    printf("Enter session cookie: ");
    fgets(cookie, COOKIE_SIZE, stdin);
    cookie[strcspn(cookie, "\n")] = '\0';

    load_session(cookie);

    return 0;
}