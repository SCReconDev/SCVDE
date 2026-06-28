#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char session_id[50];
    int user_id;
} Session;

void deserialize_session(char* data, Session* session) {
    char* token = strtok(data, "|");
    strcpy(session->session_id, token);
    token = strtok(NULL, "|");
    session->user_id = atoi(token);
}

void load_session(char* cookie) {
    Session session;
    deserialize_session(cookie, &session);
    printf("Loaded session: %s, %d\n", session.session_id, session.user_id);
}

int main() {
    char cookie[] = "abc123|1001";
    load_session(cookie);
    return 0;
}