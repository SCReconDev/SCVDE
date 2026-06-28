#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char session_id[50];
    int user_id;
} Session;

void decode_session(Session *session, const char *cookie) {
    sscanf(cookie, "%49s %d", session->session_id, &session->user_id);
}

void load_session(const char *cookie) {
    Session session;
    decode_session(&session, cookie);
    printf("Session ID: %s, User ID: %d\n", session.session_id, session.user_id);
}

int main() {
    char cookie[100];
    printf("Enter cookie: ");
    fgets(cookie, sizeof(cookie), stdin);
    load_session(cookie);
    return 0;
}