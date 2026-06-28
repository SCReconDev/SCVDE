#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* task_name;
    int task_id;
} BackgroundTask;

void run_background_task(BackgroundTask* task) {
    printf("Running background task: %s with ID: %d\n", task->task_name, task->task_id);
}

int main() {
    const char* task_data = "{\"task_name\":\"indexing\",\"task_id\":123}";
    cJSON* json = cJSON_Parse(task_data);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return EXIT_FAILURE;
    }

    BackgroundTask task;
    cJSON* task_name = cJSON_GetObjectItemCaseSensitive(json, "task_name");
    if (cJSON_IsString(task_name) && (task_name->valuestring != NULL)) {
        task.task_name = strdup(task_name->valuestring);
    } else {
        fprintf(stderr, "Invalid task name in task data\n");
        cJSON_Delete(json);
        return EXIT_FAILURE;
    }

    cJSON* task_id = cJSON_GetObjectItemCaseSensitive(json, "task_id");
    if (cJSON_IsNumber(task_id)) {
        task.task_id = task_id->valueint;
    } else {
        fprintf(stderr, "Invalid task ID in task data\n");
        free(task.task_name);
        cJSON_Delete(json);
        return EXIT_FAILURE;
    }

    run_background_task(&task);
    free(task.task_name);
    cJSON_Delete(json);
    return EXIT_SUCCESS;
}