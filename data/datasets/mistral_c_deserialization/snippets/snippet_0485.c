#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* session_id;
    int user_id;
} Session;

void load_session(char* cookie_value) {
    Session* session = (Session*)malloc(sizeof(Session));
    memcpy(session, cookie_value, sizeof(Session));
    printf("Session ID: %s, User ID: %d\n", session->session_id, session->user_id);
    free(session);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s <cookie_value>\n", argv[0]);
        return 1;
    }
    load_session(argv[1]);
    return 0;
}