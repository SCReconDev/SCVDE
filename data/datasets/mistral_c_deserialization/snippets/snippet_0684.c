#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BODY_SIZE 1024

typedef struct {
    char message[100];
    int priority;
} Message;

int validate_message(json_object *jobj) {
    json_object *jmessage, *jpriority;

    if (!json_object_object_get_ex(jobj, "message", &jmessage) ||
        !json_object_object_get_ex(jobj, "priority", &jpriority)) {
        return 0;
    }

    if (json_object_get_type(jmessage) != json_type_string ||
        json_object_get_type(jpriority) != json_type_int) {
        return 0;
    }

    return 1;
}

Message* load_message(const char *body) {
    json_object *jobj = json_tokener_parse(body);
    if (jobj == NULL) {
        return NULL;
    }

    if (!validate_message(jobj)) {
        json_object_put(jobj);
        return NULL;
    }

    Message *message = (Message*)malloc(sizeof(Message));
    if (message == NULL) {
        json_object_put(jobj);
        return NULL;
    }

    strcpy(message->message, json_object_get_string(json_object_object_get(jobj, "message")));
    message->priority = json_object_get_int(json_object_object_get(jobj, "priority"));

    json_object_put(jobj);
    return message;
}

int main() {
    char body[MAX_BODY_SIZE];
    printf("Enter message body: ");
    fgets(body, MAX_BODY_SIZE, stdin);

    Message *message = load_message(body);
    if (message != NULL) {
        printf("Message: %s\nPriority: %d\n", message->message, message->priority);
        free(message);
    } else {
        printf("Invalid message body.\n");
    }

    return 0;
}