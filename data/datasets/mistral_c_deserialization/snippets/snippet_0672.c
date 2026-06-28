#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* session_id;
    char* user_id;
} Session;

void load_session(Session* session) {
    printf("Session ID: %s, User ID: %s\n", session->session_id, session->user_id);
}

int main() {
    const char* cookie = "{\"session_id\":\"abc123\",\"user_id\":\"user123\"}";
    struct json_object* json_obj = json_tokener_parse(cookie);

    if (json_obj == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    Session session;
    json_object_object_foreach(json_obj, key, val) {
        if (strcmp(key, "session_id") == 0) {
            session.session_id = strdup(json_object_get_string(val));
        } else if (strcmp(key, "user_id") == 0) {
            session.user_id = strdup(json_object_get_string(val));
        }
    }

    load_session(&session);
    free(session.session_id);
    free(session.user_id);
    json_object_put(json_obj);

    return 0;
}