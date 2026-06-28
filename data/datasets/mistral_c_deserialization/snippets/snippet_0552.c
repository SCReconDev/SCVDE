#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* session_id;
    int user_id;
} Session;

void parse_session_cookie(const char* cookie) {
    struct json_object* parsed_json;
    struct json_object* session_id;
    struct json_object* user_id;

    parsed_json = json_tokener_parse(cookie);

    if (json_object_object_get_ex(parsed_json, "session_id", &session_id)) {
        Session* session = (Session*)malloc(sizeof(Session));
        session->session_id = strdup(json_object_get_string(session_id));

        if (json_object_object_get_ex(parsed_json, "user_id", &user_id)) {
            session->user_id = json_object_get_int(user_id);
        } else {
            session->user_id = -1;
        }

        printf("Session ID: %s, User ID: %d\n", session->session_id, session->user_id);
        free(session->session_id);
        free(session);
    }

    json_object_put(parsed_json);
}

int main() {
    const char* cookie = "{\"session_id\":\"abc123\",\"user_id\":12345}";
    parse_session_cookie(cookie);
    return 0;
}