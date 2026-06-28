#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <json-c/json.h>

typedef struct {
    char* message_id;
    char* content;
} Message;

bool validate_message_json(const char* json_str) {
    struct json_object* obj = json_tokener_parse(json_str);
    if (obj == NULL) {
        return false;
    }

    bool has_message_id = json_object_object_get_ex(obj, "message_id", NULL);
    bool has_content = json_object_object_get_ex(obj, "content", NULL);

    json_object_put(obj);
    return has_message_id && has_content;
}

Message* deserialize_message(const char* json_str) {
    if (!validate_message_json(json_str)) {
        return NULL;
    }

    struct json_object* obj = json_tokener_parse(json_str);
    Message* message = malloc(sizeof(Message));

    struct json_object* message_id_obj;
    json_object_object_get_ex(obj, "message_id", &message_id_obj);
    message->message_id = strdup(json_object_get_string(message_id_obj));

    struct json_object* content_obj;
    json_object_object_get_ex(obj, "content", &content_obj);
    message->content = strdup(json_object_get_string(content_obj));

    json_object_put(obj);
    return message;
}

void free_message(Message* message) {
    free(message->message_id);
    free(message->content);
    free(message);
}

void process_message(const char* json_str) {
    Message* message = deserialize_message(json_str);
    if (message == NULL) {
        printf("Invalid message data\n");
        return;
    }

    printf("Message ID: %s, Content: %s\n", message->message_id, message->content);
    free_message(message);
}

int main() {
    const char* json_str = "{\"message_id\":\"msg123\",\"content\":\"Hello, world!\"}";
    process_message(json_str);
    return 0;
}