#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* session_id;
    int user_id;
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

    if (session_id != NULL && json_object_get_type(session_id) == json_type_string) {
        session->session_id = strdup(json_object_get_string(session_id));
    }

    if (user_id != NULL && json_object_get_type(user_id) == json_type_int) {
        session->user_id = json_object_get_int(user_id);
    }

    json_object_put(parsed_json);
}

void load_session(const char* cookie_value) {
    Session session = {NULL, 0};
    deserialize_session(cookie_value, &session);

    if (session.session_id != NULL) {
        printf("Session ID: %s\n", session.session_id);
        free(session.session_id);
    }

    printf("User ID: %d\n", session.user_id);
}

int main() {
    const char* cookie_value = "{\"session_id\":\"abc123\",\"user_id\":42}";
    load_session(cookie_value);
    return 0;
}