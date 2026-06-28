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
    struct json_object* sender_obj;
    struct json_object* message_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "sender", &sender_obj);
    json_object_object_get_ex(parsed_json, "message", &message_obj);

    if (sender_obj != NULL && json_object_is_type(sender_obj, json_type_string)) {
        message->sender = strdup(json_object_get_string(sender_obj));
    }

    if (message_obj != NULL && json_object_is_type(message_obj, json_type_string)) {
        message->message = strdup(json_object_get_string(message_obj));
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"sender\":\"alice\",\"message\":\"Hello, Bob!\"}";
    Message message;

    deserialize_message(json_str, &message);

    printf("Sender: %s\n", message.sender);
    printf("Message: %s\n", message.message);

    free(message.sender);
    free(message.message);
    return 0;
}