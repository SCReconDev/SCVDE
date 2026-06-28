#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* session_id;
    int user_id;
} Session;

void decode_session(const char* cookie, Session* session) {
    char* token = strtok((char*)cookie, ":");
    session->session_id = strdup(token);
    token = strtok(NULL, ":");
    session->user_id = atoi(token);
}

int main() {
    char* cookie = "abc123:42";
    Session session;
    decode_session(cookie, &session);
    printf("Session ID: %s, User ID: %d\n", session.session_id, session.user_id);
    free(session.session_id);
    return 0;
}