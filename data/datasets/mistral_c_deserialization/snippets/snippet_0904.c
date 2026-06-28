#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* task;
    int priority;
} Task;

void process_task(Task* task) {
    printf("Processing task: %s with priority: %d\n", task->task, task->priority);
}

int main() {
    const char* body = "{\"task\":\"backup\",\"priority\":1}";
    cJSON* json = cJSON_Parse(body);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return EXIT_FAILURE;
    }

    Task task;
    cJSON* task_name = cJSON_GetObjectItemCaseSensitive(json, "task");
    if (cJSON_IsString(task_name) && (task_name->valuestring != NULL)) {
        task.task = strdup(task_name->valuestring);
    } else {
        fprintf(stderr, "Invalid task in body\n");
        cJSON_Delete(json);
        return EXIT_FAILURE;
    }

    cJSON* priority = cJSON_GetObjectItemCaseSensitive(json, "priority");
    if (cJSON_IsNumber(priority)) {
        task.priority = priority->valueint;
    } else {
        fprintf(stderr, "Invalid priority in body\n");
        free(task.task);
        cJSON_Delete(json);
        return EXIT_FAILURE;
    }

    process_task(&task);
    free(task.task);
    cJSON_Delete(json);
    return EXIT_SUCCESS;
}