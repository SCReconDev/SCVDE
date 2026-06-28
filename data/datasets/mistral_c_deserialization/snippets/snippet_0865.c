#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <cjson/cJSON.h>

typedef struct {
    char* task_id;
    char* description;
    bool completed;
} Task;

bool validate_task_schema(const cJSON* json) {
    if (!cJSON_IsObject(json)) return false;
    cJSON* task_id = cJSON_GetObjectItemCaseSensitive(json, "task_id");
    cJSON* description = cJSON_GetObjectItemCaseSensitive(json, "description");
    cJSON* completed = cJSON_GetObjectItemCaseSensitive(json, "completed");
    if (!cJSON_IsString(task_id) || !cJSON_IsString(description) || !cJSON_IsBool(completed)) return false;
    return true;
}

Task* deserialize_task(const char* json_str) {
    cJSON* json = cJSON_Parse(json_str);
    if (!json || !validate_task_schema(json)) {
        cJSON_Delete(json);
        return NULL;
    }

    Task* task = malloc(sizeof(Task));
    if (!task) {
        cJSON_Delete(json);
        return NULL;
    }

    cJSON* task_id = cJSON_GetObjectItemCaseSensitive(json, "task_id");
    cJSON* description = cJSON_GetObjectItemCaseSensitive(json, "description");
    cJSON* completed = cJSON_GetObjectItemCaseSensitive(json, "completed");

    task->task_id = strdup(task_id->valuestring);
    task->description = strdup(description->valuestring);
    task->completed = cJSON_IsTrue(completed);

    cJSON_Delete(json);
    return task;
}

void free_task(Task* task) {
    if (task) {
        free(task->task_id);
        free(task->description);
        free(task);
    }
}

int main() {
    const char* json_str = "{\"task_id\":\"67890\",\"description\":\"Complete project\",\"completed\":false}";
    Task* task = deserialize_task(json_str);

    if (task) {
        printf("Task ID: %s\nDescription: %s\nCompleted: %s\n", task->task_id, task->description, task->completed ? "Yes" : "No");
        free_task(task);
    } else {
        printf("Failed to deserialize task.\n");
    }

    return 0;
}