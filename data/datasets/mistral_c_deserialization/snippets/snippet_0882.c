#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* session_id;
    int user_id;
} Session;

void validate_session(Session* session) {
    if (session->user_id <= 0) {
        fprintf(stderr, "Invalid user ID\n");
        exit(1);
    }
}

int main() {
    const char* cookie_value = "{\"session_id\":\"abc123\",\"user_id\":123}";
    struct json_object* parsed_json;
    struct json_object* session_id_obj;
    struct json_object* user_id_obj;
    Session session;

    parsed_json = json_tokener_parse(cookie_value);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    if (!json_object_object_get_ex(parsed_json, "session_id", &session_id_obj) ||
        !json_object_object_get_ex(parsed_json, "user_id", &user_id_obj)) {
        fprintf(stderr, "Error extracting JSON fields\n");
        json_object_put(parsed_json);
        return 1;
    }

    session.session_id = strdup(json_object_get_string(session_id_obj));
    session.user_id = json_object_get_int(user_id_obj);

    validate_session(&session);

    printf("Session ID: %s, User ID: %d\n", session.session_id, session.user_id);

    free(session.session_id);
    json_object_put(parsed_json);

    return 0;
}