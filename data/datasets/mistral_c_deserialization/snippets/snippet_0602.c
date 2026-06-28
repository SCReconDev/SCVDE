#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* session_id;
    char* user_id;
} Session;

void process_session(Session* session) {
    printf("Session ID: %s\n", session->session_id);
    printf("User ID: %s\n", session->user_id);
}

Session* deserialize_session(const char* json_str) {
    struct json_object* parsed_json;
    struct json_object* session_id_obj;
    struct json_object* user_id_obj;
    Session* session = malloc(sizeof(Session));

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        free(session);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "session_id", &session_id_obj);
    json_object_object_get_ex(parsed_json, "user_id", &user_id_obj);

    if (session_id_obj == NULL || user_id_obj == NULL) {
        fprintf(stderr, "Invalid JSON format\n");
        json_object_put(parsed_json);
        free(session);
        return NULL;
    }

    session->session_id = strdup(json_object_get_string(session_id_obj));
    session->user_id = strdup(json_object_get_string(user_id_obj));

    json_object_put(parsed_json);
    return session;
}

int main() {
    const char* json_str = "{\"session_id\":\"abc123\",\"user_id\":\"user123\"}";
    Session* session = deserialize_session(json_str);

    if (session != NULL) {
        process_session(session);
        free(session->session_id);
        free(session->user_id);
        free(session);
    }

    return 0;
}