#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <cjson/cJSON.h>

typedef struct {
    char* message_id;
    char* content;
    int priority;
} Message;

bool validate_message_schema(cJSON* json) {
    if (!cJSON_HasObjectItem(json, "message_id") ||
        !cJSON_HasObjectItem(json, "content") ||
        !cJSON_HasObjectItem(json, "priority")) {
        return false;
    }

    cJSON* message_id = cJSON_GetObjectItemCaseSensitive(json, "message_id");
    cJSON* content = cJSON_GetObjectItemCaseSensitive(json, "content");
    cJSON* priority = cJSON_GetObjectItemCaseSensitive(json, "priority");

    if (!cJSON_IsString(message_id) || !cJSON_IsString(content) || !cJSON_IsNumber(priority)) {
        return false;
    }

    return true;
}

Message* deserialize_message(const char* json_str) {
    cJSON* json = cJSON_Parse(json_str);
    if (!json) {
        return NULL;
    }

    if (!validate_message_schema(json)) {
        cJSON_Delete(json);
        return NULL;
    }

    Message* message = (Message*)malloc(sizeof(Message));
    if (!message) {
        cJSON_Delete(json);
        return NULL;
    }

    cJSON* message_id = cJSON_GetObjectItemCaseSensitive(json, "message_id");
    cJSON* content = cJSON_GetObjectItemCaseSensitive(json, "content");
    cJSON* priority = cJSON_GetObjectItemCaseSensitive(json, "priority");

    message->message_id = strdup(message_id->valuestring);
    message->content = strdup(content->valuestring);
    message->priority = priority->valueint;

    cJSON_Delete(json);

    return message;
}

void free_message(Message* message) {
    if (message) {
        free(message->message_id);
        free(message->content);
        free(message);
    }
}

int main() {
    const char* json_str = "{\"message_id\":\"msg123\",\"content\":\"Hello, World!\",\"priority\":1}";
    Message* message = deserialize_message(json_str);

    if (message) {
        printf("Message ID: %s\n", message->message_id);
        printf("Content: %s\n", message->content);
        printf("Priority: %d\n", message->priority);
        free_message(message);
    } else {
        printf("Failed to deserialize message.\n");
    }

    return 0;
}