#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* username;
    char* session_token;
} Session;

void deserialize_session(const char* json_str, Session* session) {
    struct json_object* parsed_json;
    struct json_object* username;
    struct json_object* session_token;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (json_object_object_get_ex(parsed_json, "username", &username)) {
        session->username = strdup(json_object_get_string(username));
    }

    if (json_object_object_get_ex(parsed_json, "session_token", &session_token)) {
        session->session_token = strdup(json_object_get_string(session_token));
    }

    json_object_put(parsed_json);
}

void process_session(Session* session) {
    printf("Username: %s\n", session->username);
    printf("Session Token: %s\n", session->session_token);
}

int main() {
    const char* json_str = "{\"username\":\"johndoe\",\"session_token\":\"abc123\"}";
    Session session;

    deserialize_session(json_str, &session);
    process_session(&session);

    free(session.username);
    free(session.session_token);
    return 0;
}