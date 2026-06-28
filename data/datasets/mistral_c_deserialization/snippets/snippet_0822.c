#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *username;
    char *session_id;
} Session;

void parse_session(json_object *jobj, Session *session) {
    json_object_object_foreach(jobj, key, val) {
        if (strcmp(key, "username") == 0) {
            session->username = strdup(json_object_get_string(val));
        } else if (strcmp(key, "session_id") == 0) {
            session->session_id = strdup(json_object_get_string(val));
        }
    }
}

int main() {
    const char *cookie = "{\"username\":\"user123\",\"session_id\":\"abc123\"}";
    json_object *jobj = json_tokener_parse(cookie);

    if (jobj == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    Session session;
    parse_session(jobj, &session);

    printf("Username: %s\n", session.username);
    printf("Session ID: %s\n", session.session_id);

    free(session.username);
    free(session.session_id);
    json_object_put(jobj);

    return 0;
}