#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char message_id[MAX_BUFFER_SIZE];
    char message_body[MAX_BUFFER_SIZE];
} Message;

void process_message(const char* json_data) {
    struct json_object *parsed_json;
    struct json_object *message_id_obj, *message_body_obj;
    Message message;

    parsed_json = json_tokener_parse(json_data);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON data\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "message_id", &message_id_obj) ||
        !json_object_object_get_ex(parsed_json, "message_body", &message_body_obj)) {
        fprintf(stderr, "Error: Missing required fields in JSON data\n");
        json_object_put(parsed_json);
        return;
    }

    strncpy(message.message_id, json_object_get_string(message_id_obj), MAX_BUFFER_SIZE - 1);
    strncpy(message.message_body, json_object_get_string(message_body_obj), MAX_BUFFER_SIZE - 1);

    printf("Message ID: %s, Message Body: %s\n", message.message_id, message.message_body);

    json_object_put(parsed_json);
}

int main() {
    const char* json_data = "{\"message_id\":\"msg1\",\"message_body\":\"Hello, world!\"}";
    process_message(json_data);
    return 0;
}