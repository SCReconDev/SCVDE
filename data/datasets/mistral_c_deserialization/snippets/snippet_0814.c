#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* sender;
    char* message;
} Message;

void deserialize_message(const char* json_str, Message* message) {
    struct json_object* parsed_json;
    struct json_object* sender;
    struct json_object* message_content;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (json_object_object_get_ex(parsed_json, "sender", &sender)) {
        message->sender = strdup(json_object_get_string(sender));
    }

    if (json_object_object_get_ex(parsed_json, "message", &message_content)) {
        message->message = strdup(json_object_get_string(message_content));
    }

    json_object_put(parsed_json);
}

void process_message(Message* message) {
    printf("Sender: %s\n", message->sender);
    printf("Message: %s\n", message->message);
}

int main() {
    const char* json_str = "{\"sender\":\"alice\",\"message\":\"Hello, Bob!\"}";
    Message message;

    deserialize_message(json_str, &message);
    process_message(&message);

    free(message.sender);
    free(message.message);
    return 0;
}