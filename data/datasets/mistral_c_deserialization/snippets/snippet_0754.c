#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *sender;
    char *message;
} Message;

void deserialize_message(const char *json_str, Message *msg) {
    struct json_object *parsed_json;
    struct json_object *sender;
    struct json_object *message;

    parsed_json = json_tokener_parse(json_str);

    if (json_object_object_get_ex(parsed_json, "sender", &sender)) {
        msg->sender = strdup(json_object_get_string(sender));
    }

    if (json_object_object_get_ex(parsed_json, "message", &message)) {
        msg->message = strdup(json_object_get_string(message));
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"sender\":\"john_doe\",\"message\":\"Hello, world!\"}";
    Message msg;

    deserialize_message(json_str, &msg);

    printf("Sender: %s\n", msg.sender);
    printf("Message: %s\n", msg.message);

    free(msg.sender);
    free(msg.message);

    return 0;
}