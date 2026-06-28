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

    if (json_object_object_get_ex(parsed_json, "session_id", &session_id)) {
        session->session_id = strdup(json_object_get_string(session_id));
    }

    if (json_object_object_get_ex(parsed_json, "user_id", &user_id)) {
        session->user_id = json_object_get_int(user_id);
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"session_id\":\"abc123\",\"user_id\":12345}";
    Session session;

    deserialize_session(json_str, &session);

    printf("Session ID: %s\n", session.session_id);
    printf("User ID: %d\n", session.user_id);

    free(session.session_id);
    return 0;
}