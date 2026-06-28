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
    struct json_object* session_id_obj;
    struct json_object* user_id_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "session_id", &session_id_obj)) {
        fprintf(stderr, "Error getting session_id from JSON\n");
        json_object_put(parsed_json);
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "user_id", &user_id_obj)) {
        fprintf(stderr, "Error getting user_id from JSON\n");
        json_object_put(parsed_json);
        return;
    }

    session->session_id = strdup(json_object_get_string(session_id_obj));
    session->user_id = strdup(json_object_get_string(user_id_obj));

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"session_id\":\"abc123\",\"user_id\":\"johndoe\"}";
    Session session;

    deserialize_session(json_str, &session);

    printf("Session ID: %s\n", session.session_id);
    printf("User ID: %s\n", session.user_id);

    free(session.session_id);
    free(session.user_id);

    return 0;
}