#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* username;
    char* session_id;
} Session;

void validate_session(Session* session) {
    if (strstr(session->session_id, "invalid") != NULL) {
        fprintf(stderr, "Invalid session ID\n");
        exit(EXIT_FAILURE);
    }
    printf("Session validated for user: %s\n", session->username);
}

int main() {
    const char* cookie = "{\"username\":\"user1\",\"session_id\":\"abc123\"}";
    cJSON* json = cJSON_Parse(cookie);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return EXIT_FAILURE;
    }

    Session session;
    cJSON* username = cJSON_GetObjectItemCaseSensitive(json, "username");
    if (cJSON_IsString(username) && (username->valuestring != NULL)) {
        session.username = strdup(username->valuestring);
    } else {
        fprintf(stderr, "Invalid username in cookie\n");
        cJSON_Delete(json);
        return EXIT_FAILURE;
    }

    cJSON* session_id = cJSON_GetObjectItemCaseSensitive(json, "session_id");
    if (cJSON_IsString(session_id) && (session_id->valuestring != NULL)) {
        session.session_id = strdup(session_id->valuestring);
    } else {
        fprintf(stderr, "Invalid session ID in cookie\n");
        free(session.username);
        cJSON_Delete(json);
        return EXIT_FAILURE;
    }

    validate_session(&session);
    free(session.username);
    free(session.session_id);
    cJSON_Delete(json);
    return EXIT_SUCCESS;
}