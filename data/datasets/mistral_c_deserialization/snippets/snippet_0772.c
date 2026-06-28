#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *username;
    char *session_id;
} Session;

void parse_session_cookie(const char *cookie) {
    struct json_object *parsed_json;
    struct json_object *username;
    struct json_object *session_id;

    parsed_json = json_tokener_parse(cookie);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "username", &username)) {
        fprintf(stderr, "Username not found in JSON\n");
        json_object_put(parsed_json);
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "session_id", &session_id)) {
        fprintf(stderr, "Session ID not found in JSON\n");
        json_object_put(parsed_json);
        return;
    }

    Session session;
    session.username = strdup(json_object_get_string(username));
    session.session_id = strdup(json_object_get_string(session_id));

    printf("Username: %s, Session ID: %s\n", session.username, session.session_id);

    free(session.username);
    free(session.session_id);
    json_object_put(parsed_json);
}

int main() {
    const char *cookie = "{\"username\":\"johndoe\",\"session_id\":\"abc123\"}";
    parse_session_cookie(cookie);
    return 0;
}