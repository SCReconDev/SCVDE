#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* session_id;
    char* user_id;
} Session;

void deserialize_session(const char* json_str, Session* session) {
    struct json_object* parsed_json;
    struct json_object* session_id;
    struct json_object* user_id;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "session_id", &session_id);
    json_object_object_get_ex(parsed_json, "user_id", &user_id);

    if (session_id != NULL && json_object_is_type(session_id, json_type_string)) {
        session->session_id = strdup(json_object_get_string(session_id));
    }

    if (user_id != NULL && json_object_is_type(user_id, json_type_string)) {
        session->user_id = strdup(json_object_get_string(user_id));
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"session_id\":\"abc123\",\"user_id\":\"john_doe\"}";
    Session session;

    deserialize_session(json_str, &session);

    printf("Session ID: %s\n", session.session_id);
    printf("User ID: %s\n", session.user_id);

    free(session.session_id);
    free(session.user_id);
    return 0;
}