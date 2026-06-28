#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BODY_SIZE 1024

typedef struct {
    char message_id[256];
    int priority;
    char content[256];
} Message;

void deserialize_message(Message *message, const char *body) {
    struct json_object *parsed_json;
    struct json_object *message_id_obj, *priority_obj, *content_obj;

    parsed_json = json_tokener_parse(body);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON body\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "message_id", &message_id_obj);
    json_object_object_get_ex(parsed_json, "priority", &priority_obj);
    json_object_object_get_ex(parsed_json, "content", &content_obj);

    if (message_id_obj != NULL && json_object_is_type(message_id_obj, json_type_string)) {
        strncpy(message->message_id, json_object_get_string(message_id_obj), sizeof(message->message_id) - 1);
    }

    if (priority_obj != NULL && json_object_is_type(priority_obj, json_type_int)) {
        message->priority = json_object_get_int(priority_obj);
    }

    if (content_obj != NULL && json_object_is_type(content_obj, json_type_string)) {
        strncpy(message->content, json_object_get_string(content_obj), sizeof(message->content) - 1);
    }

    json_object_put(parsed_json);
}

int main() {
    Message message;
    char body[MAX_BODY_SIZE];

    printf("Enter message body: ");
    fgets(body, sizeof(body), stdin);

    deserialize_message(&message, body);

    printf("Deserialized Message:\n");
    printf("Message ID: %s\n", message.message_id);
    printf("Priority: %d\n", message.priority);
    printf("Content: %s\n", message.content);

    return 0;
}