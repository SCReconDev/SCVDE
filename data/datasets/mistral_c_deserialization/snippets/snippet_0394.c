#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* username;
    char* session_id;
} Session;

void load_session(Session* session) {
    printf("Username: %s\n", session->username);
    printf("Session ID: %s\n", session->session_id);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <cookie_value>\n", argv[0]);
        return 1;
    }

    char* cookie_value = argv[1];
    Session* session = (Session*)cookie_value;
    load_session(session);

    return 0;
}