#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* username;
    char* session_id;
} Session;

void decode_session(const char* cookie, Session* session) {
    char* token = strtok((char*)cookie, ";");
    session->username = strdup(token);
    token = strtok(NULL, ";");
    session->session_id = strdup(token);
}

void load_session(const char* cookie) {
    Session session;
    decode_session(cookie, &session);
    printf("Username: %s, Session ID: %s\n", session.username, session.session_id);
    free(session.username);
    free(session.session_id);
}

int main() {
    const char* cookie = "user123;abc123xyz";
    load_session(cookie);
    return 0;
}