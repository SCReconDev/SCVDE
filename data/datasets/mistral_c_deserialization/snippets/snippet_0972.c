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
    struct json_object* username;
    struct json_object* session_id;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "username", &username)) {
        fprintf(stderr, "Error: 'username' field not found\n");
        json_object_put(parsed_json);
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "session_id", &session_id)) {
        fprintf(stderr, "Error: 'session_id' field not found\n");
        json_object_put(parsed_json);
        return;
    }

    session->username = strdup(json_object_get_string(username));
    session->session_id = strdup(json_object_get_string(session_id));

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