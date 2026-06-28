#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* username;
    char* session_id;
} Session;

void load_session(const char* cookie) {
    cJSON* json = cJSON_Parse(cookie);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return;
    }

    cJSON* username = cJSON_GetObjectItemCaseSensitive(json, "username");
    cJSON* session_id = cJSON_GetObjectItemCaseSensitive(json, "session_id");

    if (cJSON_IsString(username) && (username->valuestring != NULL) && cJSON_IsString(session_id) && (session_id->valuestring != NULL)) {
        Session session;
        session.username = strdup(username->valuestring);
        session.session_id = strdup(session_id->valuestring);

        printf("Session: %s, ID: %s\n", session.username, session.session_id);

        free(session.username);
        free(session.session_id);
    }

    cJSON_Delete(json);
}

int main() {
    const char* cookie = "{\"username\":\"johndoe\",\"session_id\":\"abc123\"}";
    load_session(cookie);
    return 0;
}