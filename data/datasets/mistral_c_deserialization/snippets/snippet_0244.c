#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* session_id;
    char* user_data;
} Session;

Session* load_session(const char* cookie) {
    Session* session = malloc(sizeof(Session));
    char* token = strtok((char*)cookie, "|");
    session->session_id = strdup(token);
    token = strtok(NULL, "|");
    session->user_data = strdup(token);
    return session;
}

void process_session(const char* cookie) {
    Session* session = load_session(cookie);
    printf("Session ID: %s\n", session->session_id);
    free(session->session_id);
    free(session->user_data);
    free(session);
}

int main() {
    char* cookie = "abc123|user=admin";
    process_session(cookie);
    return 0;
}