#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char message_id[50];
    char sender[50];
    char content[200];
} Message;

int validate_message_json(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *message_id_obj, *sender_obj, *content_obj;

    parsed_json = json_tokener_parse(json_str);
    if (!parsed_json) {
        return 0;
    }

    if (!json_object_object_get_ex(parsed_json, "message_id", &message_id_obj) ||
        !json_object_object_get_ex(parsed_json, "sender", &sender_obj) ||
        !json_object_object_get_ex(parsed_json, "content", &content_obj)) {
        json_object_put(parsed_json);
        return 0;
    }

    if (json_object_get_type(message_id_obj) != json_type_string ||
        json_object_get_type(sender_obj) != json_type_string ||
        json_object_get_type(content_obj) != json_type_string) {
        json_object_put(parsed_json);
        return 0;
    }

    json_object_put(parsed_json);
    return 1;
}

Message* deserialize_message(const char *json_str) {
    Message *message = malloc(sizeof(Message));
    if (!message) {
        return NULL;
    }

    struct json_object *parsed_json;
    struct json_object *message_id_obj, *sender_obj, *content_obj;

    parsed_json = json_tokener_parse(json_str);
    if (!parsed_json) {
        free(message);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "message_id", &message_id_obj);
    json_object_object_get_ex(parsed_json, "sender", &sender_obj);
    json_object_object_get_ex(parsed_json, "content", &content_obj);

    strncpy(message->message_id, json_object_get_string(message_id_obj), sizeof(message->message_id) - 1);
    strncpy(message->sender, json_object_get_string(sender_obj), sizeof(message->sender) - 1);
    strncpy(message->content, json_object_get_string(content_obj), sizeof(message->content) - 1);

    json_object_put(parsed_json);
    return message;
}

void process_message_data(const char *json_str) {
    if (!validate_message_json(json_str)) {
        printf("Invalid message data format\n");
        return;
    }

    Message *message = deserialize_message(json_str);
    if (!message) {
        printf("Failed to deserialize message data\n");
        return;
    }

    printf("Message ID: %s, Sender: %s, Content: %s\n", message->message_id, message->sender, message->content);
    free(message);
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    printf("Enter message data in JSON format:\n");
    fgets(buffer, sizeof(buffer), stdin);

    process_message_data(buffer);

    return 0;
}