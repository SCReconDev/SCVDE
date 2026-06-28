#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* session_id;
    char* user_id;
    char* ip_address;
} Session;

void deserialize_session(const char* json_str, Session* session) {
    cJSON* json = cJSON_Parse(json_str);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return;
    }

    cJSON* session_id = cJSON_GetObjectItemCaseSensitive(json, "session_id");
    if (cJSON_IsString(session_id) && (session_id->valuestring != NULL)) {
        session->session_id = strdup(session_id->valuestring);
    }

    cJSON* user_id = cJSON_GetObjectItemCaseSensitive(json, "user_id");
    if (cJSON_IsString(user_id) && (user_id->valuestring != NULL)) {
        session->user_id = strdup(user_id->valuestring);
    }

    cJSON* ip_address = cJSON_GetObjectItemCaseSensitive(json, "ip_address");
    if (cJSON_IsString(ip_address) && (ip_address->valuestring != NULL)) {
        session->ip_address = strdup(ip_address->valuestring);
    }

    cJSON_Delete(json);
}

int main() {
    const char* json_str = "{\"session_id\":\"abc123\",\"user_id\":\"user123\",\"ip_address\":\"192.168.1.1\"}";
    Session session;

    deserialize_session(json_str, &session);

    printf("Session ID: %s\n", session.session_id);
    printf("User ID: %s\n", session.user_id);
    printf("IP Address: %s\n", session.ip_address);

    free(session.session_id);
    free(session.user_id);
    free(session.ip_address);

    return 0;
}