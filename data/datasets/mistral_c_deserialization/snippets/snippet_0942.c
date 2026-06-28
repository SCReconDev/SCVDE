#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* session_id;
    char* user_id;
} Session;

void parse_session_cookie(const char* cookie) {
    cJSON* json = cJSON_Parse(cookie);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return;
    }

    cJSON* session_id = cJSON_GetObjectItemCaseSensitive(json, "session_id");
    cJSON* user_id = cJSON_GetObjectItemCaseSensitive(json, "user_id");

    if (cJSON_IsString(session_id) && (session_id->valuestring != NULL)) {
        printf("Session ID: %s\n", session_id->valuestring);
    }

    if (cJSON_IsString(user_id) && (user_id->valuestring != NULL)) {
        printf("User ID: %s\n", user_id->valuestring);
    }

    cJSON_Delete(json);
}

int main() {
    const char* cookie = "{\"session_id\":\"abc123\",\"user_id\":\"user123\"}";
    parse_session_cookie(cookie);
    return 0;
}