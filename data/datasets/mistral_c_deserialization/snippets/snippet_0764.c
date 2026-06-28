#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* message_id;
    char* content;
} Message;

void deserialize_message(const char* json_str, Message* message) {
    struct json_object* parsed_json;
    struct json_object* message_id_obj;
    struct json_object* content_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "message_id", &message_id_obj)) {
        fprintf(stderr, "Error getting message_id from JSON\n");
        json_object_put(parsed_json);
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "content", &content_obj)) {
        fprintf(stderr, "Error getting content from JSON\n");
        json_object_put(parsed_json);
        return;
    }

    message->message_id = strdup(json_object_get_string(message_id_obj));
    message->content = strdup(json_object_get_string(content_obj));

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"message_id\":\"12345\",\"content\":\"Hello, World!\"}";
    Message message;

    deserialize_message(json_str, &message);

    printf("Message ID: %s\n", message.message_id);
    printf("Content: %s\n", message.content);

    free(message.message_id);
    free(message.content);

    return 0;
}