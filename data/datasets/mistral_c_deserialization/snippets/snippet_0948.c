#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* task_id;
    char* task_data;
} Task;

void parse_task_data(const char* data) {
    cJSON* json = cJSON_Parse(data);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return;
    }

    cJSON* task_id = cJSON_GetObjectItemCaseSensitive(json, "task_id");
    cJSON* task_data = cJSON_GetObjectItemCaseSensitive(json, "task_data");

    if (cJSON_IsString(task_id) && (task_id->valuestring != NULL)) {
        printf("Task ID: %s\n", task_id->valuestring);
    }

    if (cJSON_IsString(task_data) && (task_data->valuestring != NULL)) {
        printf("Task Data: %s\n", task_data->valuestring);
    }

    cJSON_Delete(json);
}

int main() {
    const char* data = "{\"task_id\":\"task123\",\"task_data\":\"{\\\"param1\\\":\\\"value1\\\"}\"}";
    parse_task_data(data);
    return 0;
}