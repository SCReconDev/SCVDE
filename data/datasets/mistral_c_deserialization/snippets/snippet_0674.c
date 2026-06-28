#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* message_id;
    char* content;
} Message;

void process_message(Message* message) {
    printf("Message ID: %s, Content: %s\n", message->message_id, message->content);
}

int main() {
    const char* body = "{\"message_id\":\"msg123\",\"content\":\"Hello, World!\"}";
    struct json_object* json_obj = json_tokener_parse(body);

    if (json_obj == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    Message message;
    json_object_object_foreach(json_obj, key, val) {
        if (strcmp(key, "message_id") == 0) {
            message.message_id = strdup(json_object_get_string(val));
        } else if (strcmp(key, "content") == 0) {
            message.content = strdup(json_object_get_string(val));
        }
    }

    process_message(&message);
    free(message.message_id);
    free(message.content);
    json_object_put(json_obj);

    return 0;
}