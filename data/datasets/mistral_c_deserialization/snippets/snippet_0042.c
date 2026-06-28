#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* username;
    char* session_id;
} Session;

void process_session(Session* session) {
    printf("Username: %s\n", session->username);
    printf("Session ID: %s\n", session->session_id);
}

void deserialize_session(const char* cookie, Session* session) {
    char* token = strtok((char*)cookie, "&");
    while (token != NULL) {
        char* key = strtok(NULL, "=");
        char* value = strtok(NULL, "&");
        if (strcmp(key, "username") == 0) {
            session->username = strdup(value);
        } else if (strcmp(key, "session_id") == 0) {
            session->session_id = strdup(value);
        }
        token = strtok(NULL, "&");
    }
}

void load_session(const char* cookie) {
    Session session;
    deserialize_session(cookie, &session);
    process_session(&session);
}

int main() {
    const char* cookie = "username=JohnDoe&session_id=abc123";
    load_session(cookie);
    return 0;
}