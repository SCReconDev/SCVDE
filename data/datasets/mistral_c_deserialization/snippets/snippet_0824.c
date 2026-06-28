#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *message_id;
    char *content;
} Message;

void parse_message(json_object *jobj, Message *message) {
    json_object_object_foreach(jobj, key, val) {
        if (strcmp(key, "message_id") == 0) {
            message->message_id = strdup(json_object_get_string(val));
        } else if (strcmp(key, "content") == 0) {
            message->content = strdup(json_object_get_string(val));
        }
    }
}

int main() {
    const char *body = "{\"message_id\":\"msg123\",\"content\":\"Hello, world!\"}";
    json_object *jobj = json_tokener_parse(body);

    if (jobj == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    Message message;
    parse_message(jobj, &message);

    printf("Message ID: %s\n", message.message_id);
    printf("Content: %s\n", message.content);

    free(message.message_id);
    free(message.content);
    json_object_put(jobj);

    return 0;
}