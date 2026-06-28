#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* message_id;
    char* sender;
    char* content;
} Message;

void deserialize_message(const char* json_str, Message* message) {
    cJSON* json = cJSON_Parse(json_str);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return;
    }

    cJSON* message_id = cJSON_GetObjectItemCaseSensitive(json, "message_id");
    if (cJSON_IsString(message_id) && (message_id->valuestring != NULL)) {
        message->message_id = strdup(message_id->valuestring);
    }

    cJSON* sender = cJSON_GetObjectItemCaseSensitive(json, "sender");
    if (cJSON_IsString(sender) && (sender->valuestring != NULL)) {
        message->sender = strdup(sender->valuestring);
    }

    cJSON* content = cJSON_GetObjectItemCaseSensitive(json, "content");
    if (cJSON_IsString(content) && (content->valuestring != NULL)) {
        message->content = strdup(content->valuestring);
    }

    cJSON_Delete(json);
}

int main() {
    const char* json_str = "{\"message_id\":\"msg123\",\"sender\":\"user123\",\"content\":\"Hello, world!\"}";
    Message message;

    deserialize_message(json_str, &message);

    printf("Message ID: %s\n", message.message_id);
    printf("Sender: %s\n", message.sender);
    printf("Content: %s\n", message.content);

    free(message.message_id);
    free(message.sender);
    free(message.content);

    return 0;
}