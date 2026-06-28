#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* message_id;
    char* content;
} Message;

void process_message(Message* message) {
    printf("Message ID: %s\n", message->message_id);
    printf("Content: %s\n", message->content);
}

Message* deserialize_message(const char* json_str) {
    struct json_object* parsed_json;
    struct json_object* message_id_obj;
    struct json_object* content_obj;
    Message* message = malloc(sizeof(Message));

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        free(message);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "message_id", &message_id_obj);
    json_object_object_get_ex(parsed_json, "content", &content_obj);

    if (message_id_obj == NULL || content_obj == NULL) {
        fprintf(stderr, "Invalid JSON format\n");
        json_object_put(parsed_json);
        free(message);
        return NULL;
    }

    message->message_id = strdup(json_object_get_string(message_id_obj));
    message->content = strdup(json_object_get_string(content_obj));

    json_object_put(parsed_json);
    return message;
}

int main() {
    const char* json_str = "{\"message_id\":\"msg123\",\"content\":\"Hello, world!\"}";
    Message* message = deserialize_message(json_str);

    if (message != NULL) {
        process_message(message);
        free(message->message_id);
        free(message->content);
        free(message);
    }

    return 0;
}