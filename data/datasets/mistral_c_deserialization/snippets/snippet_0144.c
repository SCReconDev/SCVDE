#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char session_id[50];
    char user_data[100];
} Session;

void deserialize_session(Session *session, const char *data) {
    memcpy(session, data, sizeof(Session));
}

void load_session(const char *cookie_value) {
    Session session;
    deserialize_session(&session, cookie_value);
    printf("Session ID: %s\n", session.session_id);
}

int main() {
    char cookie_value[150];
    printf("Enter session cookie: ");
    fgets(cookie_value, sizeof(cookie_value), stdin);
    cookie_value[strcspn(cookie_value, "\n")] = '\0';

    load_session(cookie_value);
    return 0;
}