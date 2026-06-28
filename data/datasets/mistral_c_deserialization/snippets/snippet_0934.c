#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* sender;
    char* recipient;
    char* message;
} Email;

void deserialize_email(const char* json_str, Email* email) {
    struct json_object* parsed_json;
    struct json_object* sender;
    struct json_object* recipient;
    struct json_object* message;

    parsed_json = json_tokener_parse(json_str);

    if (json_object_object_get_ex(parsed_json, "sender", &sender)) {
        email->sender = strdup(json_object_get_string(sender));
    }

    if (json_object_object_get_ex(parsed_json, "recipient", &recipient)) {
        email->recipient = strdup(json_object_get_string(recipient));
    }

    if (json_object_object_get_ex(parsed_json, "message", &message)) {
        email->message = strdup(json_object_get_string(message));
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"sender\":\"john.doe@example.com\",\"recipient\":\"jane.doe@example.com\",\"message\":\"Hello, Jane!\"}";
    Email email;

    deserialize_email(json_str, &email);

    printf("Sender: %s\n", email.sender);
    printf("Recipient: %s\n", email.recipient);
    printf("Message: %s\n", email.message);

    free(email.sender);
    free(email.recipient);
    free(email.message);

    return 0;
}