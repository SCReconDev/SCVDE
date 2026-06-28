#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <cjson/cJSON.h>

typedef struct {
    char* task_id;
    char* description;
    int priority;
} Task;

bool validate_task_schema(cJSON* json) {
    if (!cJSON_HasObjectItem(json, "task_id") ||
        !cJSON_HasObjectItem(json, "description") ||
        !cJSON_HasObjectItem(json, "priority")) {
        return false;
    }

    cJSON* task_id = cJSON_GetObjectItemCaseSensitive(json, "task_id");
    cJSON* description = cJSON_GetObjectItemCaseSensitive(json, "description");
    cJSON* priority = cJSON_GetObjectItemCaseSensitive(json, "priority");

    if (!cJSON_IsString(task_id) || !cJSON_IsString(description) || !cJSON_IsNumber(priority)) {
        return false;
    }

    return true;
}

Task* deserialize_task(const char* json_str) {
    cJSON* json = cJSON_Parse(json_str);
    if (!json) {
        return NULL;
    }

    if (!validate_task_schema(json)) {
        cJSON_Delete(json);
        return NULL;
    }

    Task* task = (Task*)malloc(sizeof(Task));
    if (!task) {
        cJSON_Delete(json);
        return NULL;
    }

    cJSON* task_id = cJSON_GetObjectItemCaseSensitive(json, "task_id");
    cJSON* description = cJSON_GetObjectItemCaseSensitive(json, "description");
    cJSON* priority = cJSON_GetObjectItemCaseSensitive(json, "priority");

    task->task_id = strdup(task_id->valuestring);
    task->description = strdup(description->valuestring);
    task->priority = priority->valueint;

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
    const char* json_str = "{\"task_id\":\"task123\",\"description\":\"Process data\",\"priority\":2}";
    Task* task = deserialize_task(json_str);

    if (task) {
        printf("Task ID: %s\n", task->task_id);
        printf("Description: %s\n", task->description);
        printf("Priority: %d\n", task->priority);
        free_task(task);
    } else {
        printf("Failed to deserialize task.\n");
    }

    return 0;
}