#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <json-c/json.h>

typedef struct {
    char* username;
    char* session_id;
} Session;

bool validate_session_json(const char* json_str) {
    struct json_object* obj = json_tokener_parse(json_str);
    if (obj == NULL) {
        return false;
    }

    bool has_username = json_object_object_get_ex(obj, "username", NULL);
    bool has_session_id = json_object_object_get_ex(obj, "session_id", NULL);

    json_object_put(obj);
    return has_username && has_session_id;
}

Session* deserialize_session(const char* json_str) {
    if (!validate_session_json(json_str)) {
        return NULL;
    }

    struct json_object* obj = json_tokener_parse(json_str);
    Session* session = malloc(sizeof(Session));

    struct json_object* username_obj;
    json_object_object_get_ex(obj, "username", &username_obj);
    session->username = strdup(json_object_get_string(username_obj));

    struct json_object* session_id_obj;
    json_object_object_get_ex(obj, "session_id", &session_id_obj);
    session->session_id = strdup(json_object_get_string(session_id_obj));

    json_object_put(obj);
    return session;
}

void free_session(Session* session) {
    free(session->username);
    free(session->session_id);
    free(session);
}

void load_session(const char* json_str) {
    Session* session = deserialize_session(json_str);
    if (session == NULL) {
        printf("Invalid session data\n");
        return;
    }

    printf("Username: %s, Session ID: %s\n", session->username, session->session_id);
    free_session(session);
}

int main() {
    const char* json_str = "{\"username\":\"johndoe\",\"session_id\":\"abc123\"}";
    load_session(json_str);
    return 0;
}