#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char username[MAX_BUFFER_SIZE];
    char session_id[MAX_BUFFER_SIZE];
} Session;

void load_session(const char *json_str, Session *session) {
    struct json_object *parsed_json;
    struct json_object *username_obj;
    struct json_object *session_id_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "username", &username_obj);
    if (username_obj != NULL) {
        strncpy(session->username, json_object_get_string(username_obj), MAX_BUFFER_SIZE - 1);
    }

    json_object_object_get_ex(parsed_json, "session_id", &session_id_obj);
    if (session_id_obj != NULL) {
        strncpy(session->session_id, json_object_get_string(session_id_obj), MAX_BUFFER_SIZE - 1);
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"username\":\"johndoe\",\"session_id\":\"abc123\"}";
    Session session;

    load_session(json_str, &session);

    printf("Username: %s\n", session.username);
    printf("Session ID: %s\n", session.session_id);

    return 0;
}