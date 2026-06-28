#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* task_id;
    char* task_name;
    char* task_data;
} TaskData;

void deserialize_task_data(const char* json_str, TaskData* task_data) {
    cJSON* json = cJSON_Parse(json_str);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return;
    }

    cJSON* task_id = cJSON_GetObjectItemCaseSensitive(json, "task_id");
    if (cJSON_IsString(task_id) && (task_id->valuestring != NULL)) {
        task_data->task_id = strdup(task_id->valuestring);
    }

    cJSON* task_name = cJSON_GetObjectItemCaseSensitive(json, "task_name");
    if (cJSON_IsString(task_name) && (task_name->valuestring != NULL)) {
        task_data->task_name = strdup(task_name->valuestring);
    }

    cJSON* task_data_json = cJSON_GetObjectItemCaseSensitive(json, "task_data");
    if (cJSON_IsString(task_data_json) && (task_data_json->valuestring != NULL)) {
        task_data->task_data = strdup(task_data_json->valuestring);
    }

    cJSON_Delete(json);
}

int main() {
    const char* json_str = "{\"task_id\":\"task123\",\"task_name\":\"example_task\",\"task_data\":\"Task data for example task.\"}";
    TaskData task_data;

    deserialize_task_data(json_str, &task_data);

    printf("Task ID: %s\n", task_data.task_id);
    printf("Task Name: %s\n", task_data.task_name);
    printf("Task Data: %s\n", task_data.task_data);

    free(task_data.task_id);
    free(task_data.task_name);
    free(task_data.task_data);

    return 0;
}