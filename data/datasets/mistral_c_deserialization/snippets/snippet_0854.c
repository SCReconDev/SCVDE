#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char message_id[50];
    char body[200];
} Message;

int deserialize_message(const char* json_str, Message* message) {
    struct json_object *parsed_json;
    struct json_object *message_id_obj, *body_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return -1;
    }

    if (!json_object_object_get_ex(parsed_json, "message_id", &message_id_obj)) {
        fprintf(stderr, "Error getting message_id\n");
        json_object_put(parsed_json);
        return -1;
    }

    if (!json_object_object_get_ex(parsed_json, "body", &body_obj)) {
        fprintf(stderr, "Error getting body\n");
        json_object_put(parsed_json);
        return -1;
    }

    strncpy(message->message_id, json_object_get_string(message_id_obj), sizeof(message->message_id) - 1);
    strncpy(message->body, json_object_get_string(body_obj), sizeof(message->body) - 1);

    json_object_put(parsed_json);
    return 0;
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    Message message;

    printf("Enter message JSON: ");
    fgets(buffer, sizeof(buffer), stdin);

    if (deserialize_message(buffer, &message) == 0) {
        printf("Deserialized Message: ID=%s, Body=%s\n", message.message_id, message.body);
    } else {
        fprintf(stderr, "Failed to deserialize message\n");
    }

    return 0;
}