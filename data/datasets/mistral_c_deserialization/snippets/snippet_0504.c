#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* task_id;
    char* payload;
} Task;

void process_message(const char* body) {
    cJSON* json = cJSON_Parse(body);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return;
    }

    cJSON* task_id = cJSON_GetObjectItemCaseSensitive(json, "task_id");
    cJSON* payload = cJSON_GetObjectItemCaseSensitive(json, "payload");

    if (cJSON_IsString(task_id) && (task_id->valuestring != NULL) && cJSON_IsString(payload) && (payload->valuestring != NULL)) {
        Task task;
        task.task_id = strdup(task_id->valuestring);
        task.payload = strdup(payload->valuestring);

        printf("Task ID: %s, Payload: %s\n", task.task_id, task.payload);

        free(task.task_id);
        free(task.payload);
    }

    cJSON_Delete(json);
}

int main() {
    const char* body = "{\"task_id\":\"123\",\"payload\":\"process_data\"}";
    process_message(body);
    return 0;
}