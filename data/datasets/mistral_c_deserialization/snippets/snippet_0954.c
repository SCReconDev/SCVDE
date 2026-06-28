#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *message_id;
    char *content;
} Message;

void process_message(const char *body, Message *message) {
    struct json_object *parsed_json;
    struct json_object *message_id_obj;
    struct json_object *content_obj;

    parsed_json = json_tokener_parse(body);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (json_object_object_get_ex(parsed_json, "message_id", &message_id_obj)) {
        message->message_id = strdup(json_object_get_string(message_id_obj));
    }

    if (json_object_object_get_ex(parsed_json, "content", &content_obj)) {
        message->content = strdup(json_object_get_string(content_obj));
    }

    json_object_put(parsed_json);
}

int main() {
    const char *body = "{\"message_id\":\"msg123\",\"content\":\"Hello, World!\"}";
    Message message;

    process_message(body, &message);

    printf("Message ID: %s\n", message.message_id);
    printf("Content: %s\n", message.content);

    free(message.message_id);
    free(message.content);
    return 0;
}