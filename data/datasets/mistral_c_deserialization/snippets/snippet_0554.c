#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* message_id;
    char* content;
} Message;

void parse_message_body(const char* body) {
    struct json_object* parsed_json;
    struct json_object* message_id;
    struct json_object* content;

    parsed_json = json_tokener_parse(body);

    if (json_object_object_get_ex(parsed_json, "message_id", &message_id)) {
        Message* message = (Message*)malloc(sizeof(Message));
        message->message_id = strdup(json_object_get_string(message_id));

        if (json_object_object_get_ex(parsed_json, "content", &content)) {
            message->content = strdup(json_object_get_string(content));
        } else {
            message->content = strdup("");
        }

        printf("Message ID: %s, Content: %s\n", message->message_id, message->content);
        free(message->message_id);
        free(message->content);
        free(message);
    }

    json_object_put(parsed_json);
}

int main() {
    const char* body = "{\"message_id\":\"msg123\",\"content\":\"Hello, world!\"}";
    parse_message_body(body);
    return 0;
}