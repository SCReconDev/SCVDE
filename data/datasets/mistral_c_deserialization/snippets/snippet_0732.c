#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char session_id[50];
    char user_id[50];
    char role[20];
} Session;

bool validate_session(Session* session) {
    if (strlen(session->session_id) == 0 || strlen(session->user_id) == 0 || strlen(session->role) == 0) {
        return false;
    }
    return true;
}

void load_session(Session* session) {
    if (validate_session(session)) {
        printf("Session loaded: %s, %s, %s\n", session->session_id, session->user_id, session->role);
    } else {
        printf("Invalid session data\n");
    }
}

int main() {
    Session session1 = {"abc123", "user123", "admin"};
    Session session2 = {"", "user456", ""};

    load_session(&session1);
    load_session(&session2);

    return 0;
}