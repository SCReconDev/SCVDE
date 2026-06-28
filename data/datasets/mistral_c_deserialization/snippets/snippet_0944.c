#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* message_id;
    char* content;
} Message;

void parse_message_body(const char* body) {
    cJSON* json = cJSON_Parse(body);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return;
    }

    cJSON* message_id = cJSON_GetObjectItemCaseSensitive(json, "message_id");
    cJSON* content = cJSON_GetObjectItemCaseSensitive(json, "content");

    if (cJSON_IsString(message_id) && (message_id->valuestring != NULL)) {
        printf("Message ID: %s\n", message_id->valuestring);
    }

    if (cJSON_IsString(content) && (content->valuestring != NULL)) {
        printf("Content: %s\n", content->valuestring);
    }

    cJSON_Delete(json);
}

int main() {
    const char* body = "{\"message_id\":\"msg123\",\"content\":\"Hello, World!\"}";
    parse_message_body(body);
    return 0;
}