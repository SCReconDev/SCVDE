#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char message_id[50];
    char sender[50];
    char content[100];
} Message;

int validate_message(Message *message) {
    if (strlen(message->message_id) == 0 || strlen(message->sender) == 0 || strlen(message->content) == 0) {
        return 0;
    }
    return 1;
}

Message* deserialize_message(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *message_id_obj, *sender_obj, *content_obj;
    Message *message = (Message*)malloc(sizeof(Message));

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        free(message);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "message_id", &message_id_obj);
    json_object_object_get_ex(parsed_json, "sender", &sender_obj);
    json_object_object_get_ex(parsed_json, "content", &content_obj);

    if (message_id_obj == NULL || sender_obj == NULL || content_obj == NULL) {
        json_object_put(parsed_json);
        free(message);
        return NULL;
    }

    strncpy(message->message_id, json_object_get_string(message_id_obj), sizeof(message->message_id) - 1);
    strncpy(message->sender, json_object_get_string(sender_obj), sizeof(message->sender) - 1);
    strncpy(message->content, json_object_get_string(content_obj), sizeof(message->content) - 1);

    json_object_put(parsed_json);

    if (!validate_message(message)) {
        free(message);
        return NULL;
    }

    return message;
}

void process_message(Message *message) {
    printf("Message ID: %s\n", message->message_id);
    printf("Sender: %s\n", message->sender);
    printf("Content: %s\n", message->content);
}

int main() {
    char json_str[MAX_BUFFER_SIZE];
    Message *message;

    printf("Enter message data in JSON format:\n");
    fgets(json_str, MAX_BUFFER_SIZE, stdin);

    message = deserialize_message(json_str);
    if (message == NULL) {
        printf("Invalid message data\n");
        return 1;
    }

    process_message(message);
    free(message);

    return 0;
}