#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char session_id[50];
    char user_id[50];
    char role[50];
} Session;

int validate_session(Session *session) {
    if (strlen(session->session_id) == 0 || strlen(session->user_id) == 0 || strlen(session->role) == 0) {
        return 0;
    }
    return 1;
}

Session* deserialize_session(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *session_id_obj, *user_id_obj, *role_obj;
    Session *session = (Session*)malloc(sizeof(Session));

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        free(session);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "session_id", &session_id_obj);
    json_object_object_get_ex(parsed_json, "user_id", &user_id_obj);
    json_object_object_get_ex(parsed_json, "role", &role_obj);

    if (session_id_obj == NULL || user_id_obj == NULL || role_obj == NULL) {
        json_object_put(parsed_json);
        free(session);
        return NULL;
    }

    strncpy(session->session_id, json_object_get_string(session_id_obj), sizeof(session->session_id) - 1);
    strncpy(session->user_id, json_object_get_string(user_id_obj), sizeof(session->user_id) - 1);
    strncpy(session->role, json_object_get_string(role_obj), sizeof(session->role) - 1);

    json_object_put(parsed_json);

    if (!validate_session(session)) {
        free(session);
        return NULL;
    }

    return session;
}

void process_session(Session *session) {
    printf("Session ID: %s\n", session->session_id);
    printf("User ID: %s\n", session->user_id);
    printf("Role: %s\n", session->role);
}

int main() {
    char json_str[MAX_BUFFER_SIZE];
    Session *session;

    printf("Enter session data in JSON format:\n");
    fgets(json_str, MAX_BUFFER_SIZE, stdin);

    session = deserialize_session(json_str);
    if (session == NULL) {
        printf("Invalid session data\n");
        return 1;
    }

    process_session(session);
    free(session);

    return 0;
}