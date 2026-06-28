#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char sender[MAX_BUFFER_SIZE];
    char message[MAX_BUFFER_SIZE];
} Message;

void process_message(const char *json_str, Message *message) {
    struct json_object *parsed_json;
    struct json_object *sender_obj;
    struct json_object *message_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "sender", &sender_obj);
    if (sender_obj != NULL) {
        strncpy(message->sender, json_object_get_string(sender_obj), MAX_BUFFER_SIZE - 1);
    }

    json_object_object_get_ex(parsed_json, "message", &message_obj);
    if (message_obj != NULL) {
        strncpy(message->message, json_object_get_string(message_obj), MAX_BUFFER_SIZE - 1);
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"sender\":\"alice\",\"message\":\"Hello, Bob!\"}";
    Message message;

    process_message(json_str, &message);

    printf("Sender: %s\n", message.sender);
    printf("Message: %s\n", message.message);

    return 0;
}