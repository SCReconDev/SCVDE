#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char username[50];
    char session_id[100];
} Session;

int deserialize_session(const char* json_str, Session* session) {
    struct json_object *parsed_json;
    struct json_object *username_obj, *session_id_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return -1;
    }

    if (!json_object_object_get_ex(parsed_json, "username", &username_obj)) {
        fprintf(stderr, "Error getting username\n");
        json_object_put(parsed_json);
        return -1;
    }

    if (!json_object_object_get_ex(parsed_json, "session_id", &session_id_obj)) {
        fprintf(stderr, "Error getting session_id\n");
        json_object_put(parsed_json);
        return -1;
    }

    strncpy(session->username, json_object_get_string(username_obj), sizeof(session->username) - 1);
    strncpy(session->session_id, json_object_get_string(session_id_obj), sizeof(session->session_id) - 1);

    json_object_put(parsed_json);
    return 0;
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    Session session;

    printf("Enter session JSON: ");
    fgets(buffer, sizeof(buffer), stdin);

    if (deserialize_session(buffer, &session) == 0) {
        printf("Deserialized Session: Username=%s, Session ID=%s\n", session.username, session.session_id);
    } else {
        fprintf(stderr, "Failed to deserialize session\n");
    }

    return 0;
}