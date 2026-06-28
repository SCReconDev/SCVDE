#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_INPUT_SIZE 1024

typedef struct {
    char session_id[256];
    char user_id[256];
    int is_admin;
} Session;

int validate_session(Session *session) {
    if (strlen(session->session_id) == 0 || strlen(session->user_id) == 0) {
        return 0;
    }
    return 1;
}

Session* deserialize_session(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *session_id_obj, *user_id_obj, *is_admin_obj;
    Session *session = malloc(sizeof(Session));

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        free(session);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "session_id", &session_id_obj);
    json_object_object_get_ex(parsed_json, "user_id", &user_id_obj);
    json_object_object_get_ex(parsed_json, "is_admin", &is_admin_obj);

    if (session_id_obj == NULL || user_id_obj == NULL || is_admin_obj == NULL) {
        json_object_put(parsed_json);
        free(session);
        return NULL;
    }

    strncpy(session->session_id, json_object_get_string(session_id_obj), sizeof(session->session_id) - 1);
    strncpy(session->user_id, json_object_get_string(user_id_obj), sizeof(session->user_id) - 1);
    session->is_admin = json_object_get_int(is_admin_obj);

    json_object_put(parsed_json);

    if (!validate_session(session)) {
        free(session);
        return NULL;
    }

    return session;
}

void process_session(Session *session) {
    printf("Processing session: %s, %s, %d\n", session->session_id, session->user_id, session->is_admin);
}

int main() {
    char input[MAX_INPUT_SIZE];
    Session *session;

    printf("Enter session data in JSON format: ");
    fgets(input, sizeof(input), stdin);

    session = deserialize_session(input);
    if (session == NULL) {
        printf("Invalid session data\n");
        return 1;
    }

    process_session(session);

    free(session);
    return 0;
}