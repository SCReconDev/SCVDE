#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *username;
    char *session_id;
} Session;

void load_session(const char *cookie, Session *session) {
    struct json_object *parsed_json;
    struct json_object *username_obj;
    struct json_object *session_id_obj;

    parsed_json = json_tokener_parse(cookie);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (json_object_object_get_ex(parsed_json, "username", &username_obj)) {
        session->username = strdup(json_object_get_string(username_obj));
    }

    if (json_object_object_get_ex(parsed_json, "session_id", &session_id_obj)) {
        session->session_id = strdup(json_object_get_string(session_id_obj));
    }

    json_object_put(parsed_json);
}

int main() {
    const char *cookie = "{\"username\":\"johndoe\",\"session_id\":\"abc123\"}";
    Session session;

    load_session(cookie, &session);

    printf("Username: %s\n", session.username);
    printf("Session ID: %s\n", session.session_id);

    free(session.username);
    free(session.session_id);
    return 0;
}