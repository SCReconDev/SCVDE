#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* username;
    char* session_id;
} Session;

void deserialize_session(const char* json_str, Session* session) {
    struct json_object* parsed_json;
    struct json_object* username_obj;
    struct json_object* session_id_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "username", &username_obj);
    json_object_object_get_ex(parsed_json, "session_id", &session_id_obj);

    if (username_obj != NULL && json_object_is_type(username_obj, json_type_string)) {
        session->username = strdup(json_object_get_string(username_obj));
    }

    if (session_id_obj != NULL && json_object_is_type(session_id_obj, json_type_string)) {
        session->session_id = strdup(json_object_get_string(session_id_obj));
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"username\":\"john_doe\",\"session_id\":\"abc123\"}";
    Session session;

    deserialize_session(json_str, &session);

    printf("Username: %s\n", session.username);
    printf("Session ID: %s\n", session.session_id);

    free(session.username);
    free(session.session_id);
    return 0;
}