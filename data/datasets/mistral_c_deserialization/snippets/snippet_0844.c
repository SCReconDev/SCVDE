#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_MESSAGE_SIZE 2048

typedef struct {
    char sender[50];
    char message[200];
} Message;

void process_message(const char *message_data) {
    struct json_object *parsed_json;
    struct json_object *sender_obj, *message_obj;
    Message msg;

    parsed_json = json_tokener_parse(message_data);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing message data\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "sender", &sender_obj) ||
        !json_object_object_get_ex(parsed_json, "message", &message_obj)) {
        fprintf(stderr, "Invalid message format\n");
        json_object_put(parsed_json);
        return;
    }

    strncpy(msg.sender, json_object_get_string(sender_obj), sizeof(msg.sender) - 1);
    strncpy(msg.message, json_object_get_string(message_obj), sizeof(msg.message) - 1);

    printf("Sender: %s\n", msg.sender);
    printf("Message: %s\n", msg.message);

    json_object_put(parsed_json);
}

int main() {
    char message[MAX_MESSAGE_SIZE];
    printf("Enter message data: ");
    fgets(message, sizeof(message), stdin);

    process_message(message);

    return 0;
}