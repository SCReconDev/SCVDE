#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_COOKIE_SIZE 256

typedef struct {
    char username[50];
    char session_id[50];
} Session;

void load_session_data(const char *cookie_value) {
    struct json_object *parsed_json;
    struct json_object *username_obj, *session_id_obj;
    Session session;

    parsed_json = json_tokener_parse(cookie_value);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing cookie data\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "username", &username_obj) ||
        !json_object_object_get_ex(parsed_json, "session_id", &session_id_obj)) {
        fprintf(stderr, "Invalid cookie format\n");
        json_object_put(parsed_json);
        return;
    }

    strncpy(session.username, json_object_get_string(username_obj), sizeof(session.username) - 1);
    strncpy(session.session_id, json_object_get_string(session_id_obj), sizeof(session.session_id) - 1);

    printf("Username: %s\n", session.username);
    printf("Session ID: %s\n", session.session_id);

    json_object_put(parsed_json);
}

int main() {
    char cookie[MAX_COOKIE_SIZE];
    printf("Enter cookie data: ");
    fgets(cookie, sizeof(cookie), stdin);

    load_session_data(cookie);

    return 0;
}