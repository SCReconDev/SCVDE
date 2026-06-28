#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char session_id[50];
    char user_id[50];
    int expiration_time;
} Session;

int validate_session_json(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *session_id_obj, *user_id_obj, *expiration_time_obj;

    parsed_json = json_tokener_parse(json_str);
    if (!parsed_json) {
        return 0;
    }

    if (!json_object_object_get_ex(parsed_json, "session_id", &session_id_obj) ||
        !json_object_object_get_ex(parsed_json, "user_id", &user_id_obj) ||
        !json_object_object_get_ex(parsed_json, "expiration_time", &expiration_time_obj)) {
        json_object_put(parsed_json);
        return 0;
    }

    if (json_object_get_type(session_id_obj) != json_type_string ||
        json_object_get_type(user_id_obj) != json_type_string ||
        json_object_get_type(expiration_time_obj) != json_type_int) {
        json_object_put(parsed_json);
        return 0;
    }

    json_object_put(parsed_json);
    return 1;
}

Session* deserialize_session(const char *json_str) {
    Session *session = malloc(sizeof(Session));
    if (!session) {
        return NULL;
    }

    struct json_object *parsed_json;
    struct json_object *session_id_obj, *user_id_obj, *expiration_time_obj;

    parsed_json = json_tokener_parse(json_str);
    if (!parsed_json) {
        free(session);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "session_id", &session_id_obj);
    json_object_object_get_ex(parsed_json, "user_id", &user_id_obj);
    json_object_object_get_ex(parsed_json, "expiration_time", &expiration_time_obj);

    strncpy(session->session_id, json_object_get_string(session_id_obj), sizeof(session->session_id) - 1);
    strncpy(session->user_id, json_object_get_string(user_id_obj), sizeof(session->user_id) - 1);
    session->expiration_time = json_object_get_int(expiration_time_obj);

    json_object_put(parsed_json);
    return session;
}

void process_session_data(const char *json_str) {
    if (!validate_session_json(json_str)) {
        printf("Invalid session data format\n");
        return;
    }

    Session *session = deserialize_session(json_str);
    if (!session) {
        printf("Failed to deserialize session data\n");
        return;
    }

    printf("Session ID: %s, User ID: %s, Expiration Time: %d\n", session->session_id, session->user_id, session->expiration_time);
    free(session);
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    printf("Enter session data in JSON format:\n");
    fgets(buffer, sizeof(buffer), stdin);

    process_session_data(buffer);

    return 0;
}