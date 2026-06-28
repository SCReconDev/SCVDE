#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* session_id;
    int user_id;
} Session;

void load_session(const char* cookie) {
    Session* session = (Session*)cookie;
    printf("Session ID: %s, User ID: %d\n", session->session_id, session->user_id);
}

int main() {
    const char* cookie = "1234567890abcdef1234567890abcdef\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0