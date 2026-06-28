#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <cjson/cJSON.h>

typedef struct {
    char* session_id;
    char* user_id;
    int expiration;
} Session;

bool validate_session_schema(cJSON* json) {
    if (!cJSON_HasObjectItem(json, "session_id") ||
        !cJSON_HasObjectItem(json, "user_id") ||
        !cJSON_HasObjectItem(json, "expiration")) {
        return false;
    }

    cJSON* session_id = cJSON_GetObjectItemCaseSensitive(json, "session_id");
    cJSON* user_id = cJSON_GetObjectItemCaseSensitive(json, "user_id");
    cJSON* expiration = cJSON_GetObjectItemCaseSensitive(json, "expiration");

    if (!cJSON_IsString(session_id) || !cJSON_IsString(user_id) || !cJSON_IsNumber(expiration)) {
        return false;
    }

    return true;
}

Session* deserialize_session(const char* json_str) {
    cJSON* json = cJSON_Parse(json_str);
    if (!json) {
        return NULL;
    }

    if (!validate_session_schema(json)) {
        cJSON_Delete(json);
        return NULL;
    }

    Session* session = (Session*)malloc(sizeof(Session));
    if (!session) {
        cJSON_Delete(json);
        return NULL;
    }

    cJSON* session_id = cJSON_GetObjectItemCaseSensitive(json, "session_id");
    cJSON* user_id = cJSON_GetObjectItemCaseSensitive(json, "user_id");
    cJSON* expiration = cJSON_GetObjectItemCaseSensitive(json, "expiration");

    session->session_id = strdup(session_id->valuestring);
    session->user_id = strdup(user_id->valuestring);
    session->expiration = expiration->valueint;

    cJSON_Delete(json);

    return session;
}

void free_session(Session* session) {
    if (session) {
        free(session->session_id);
        free(session->user_id);
        free(session);
    }
}

int main() {
    const char* json_str = "{\"session_id\":\"abc123\",\"user_id\":\"user456\",\"expiration\":3600}";
    Session* session = deserialize_session(json_str);

    if (session) {
        printf("Session ID: %s\n", session->session_id);
        printf("User ID: %s\n", session->user_id);
        printf("Expiration: %d\n", session->expiration);
        free_session(session);
    } else {
        printf("Failed to deserialize session.\n");
    }

    return 0;
}