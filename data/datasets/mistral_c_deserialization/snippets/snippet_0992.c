#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_COOKIE_SIZE 1024

typedef struct {
    char session_id[256];
    int user_id;
    char username[256];
} Session;

void deserialize_session(Session *session, const char *cookie_value) {
    struct json_object *parsed_json;
    struct json_object *session_id_obj, *user_id_obj, *username_obj;

    parsed_json = json_tokener_parse(cookie_value);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON cookie value\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "session_id", &session_id_obj);
    json_object_object_get_ex(parsed_json, "user_id", &user_id_obj);
    json_object_object_get_ex(parsed_json, "username", &username_obj);

    if (session_id_obj != NULL && json_object_is_type(session_id_obj, json_type_string)) {
        strncpy(session->session_id, json_object_get_string(session_id_obj), sizeof(session->session_id) - 1);
    }

    if (user_id_obj != NULL && json_object_is_type(user_id_obj, json_type_int)) {
        session->user_id = json_object_get_int(user_id_obj);
    }

    if (username_obj != NULL && json_object_is_type(username_obj, json_type_string)) {
        strncpy(session->username, json_object_get_string(username_obj), sizeof(session->username) - 1);
    }

    json_object_put(parsed_json);
}

int main() {
    Session session;
    char cookie_value[MAX_COOKIE_SIZE];

    printf("Enter cookie value: ");
    fgets(cookie_value, sizeof(cookie_value), stdin);

    deserialize_session(&session, cookie_value);

    printf("Deserialized Session:\n");
    printf("Session ID: %s\n", session.session_id);
    printf("User ID: %d\n", session.user_id);
    printf("Username: %s\n", session.username);

    return 0;
}