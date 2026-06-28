#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char session_id[37];
    char user_id[37];
    bool is_admin;
} Session;

bool validate_session(Session* session) {
    if (strlen(session->session_id) != 36 || strlen(session->user_id) != 36) {
        return false;
    }
    for (int i = 0; i < 36; i++) {
        if (i == 8 || i == 13 || i == 18 || i == 23) {
            if (session->session_id[i] != '-') {
                return false;
            }
        } else if (!((session->session_id[i] >= '0' && session->session_id[i] <= '9') ||
                    (session->session_id[i] >= 'a' && session->session_id[i] <= 'f'))) {
            return false;
        }
    }
    return true;
}

void process_session(Session* session) {
    if (validate_session(session)) {
        printf("Session ID: %s, User ID: %s, Admin: %s\n", session->session_id, session->user_id, session->is_admin ? "Yes" : "No");
    } else {
        printf("Invalid session data\n");
    }
}

int main() {
    Session session1 = {"123e4567-e89b-12d3-a456-426614174000", "123e4567-e89b-12d3-a456-426614174001", true};
    Session session2 = {"invalid-session-id", "invalid-user-id", false};

    process_session(&session1);
    process_session(&session2);

    return 0;
}