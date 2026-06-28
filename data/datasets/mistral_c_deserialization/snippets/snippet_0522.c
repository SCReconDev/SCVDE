#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char session_id[MAX_BUFFER_SIZE];
    char user_data[MAX_BUFFER_SIZE];
} Session;

void load_session_data(const char* json_data) {
    struct json_object *parsed_json;
    struct json_object *session_id_obj, *user_data_obj;
    Session session;

    parsed_json = json_tokener_parse(json_data);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON data\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "session_id", &session_id_obj) ||
        !json_object_object_get_ex(parsed_json, "user_data", &user_data_obj)) {
        fprintf(stderr, "Error: Missing required fields in JSON data\n");
        json_object_put(parsed_json);
        return;
    }

    strncpy(session.session_id, json_object_get_string(session_id_obj), MAX_BUFFER_SIZE - 1);
    strncpy(session.user_data, json_object_get_string(user_data_obj), MAX_BUFFER_SIZE - 1);

    printf("Session ID: %s, User Data: %s\n", session.session_id, session.user_data);

    json_object_put(parsed_json);
}

int main() {
    const char* json_data = "{\"session_id\":\"abc123\",\"user_data\":\"user_data_here\"}";
    load_session_data(json_data);
    return 0;
}