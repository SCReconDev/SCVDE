#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <json-c/json.h>

typedef struct {
    char* task_id;
    char* task_data;
} Task;

bool validate_task_json(const char* json_str) {
    struct json_object* obj = json_tokener_parse(json_str);
    if (obj == NULL) {
        return false;
    }

    bool has_task_id = json_object_object_get_ex(obj, "task_id", NULL);
    bool has_task_data = json_object_object_get_ex(obj, "task_data", NULL);

    json_object_put(obj);
    return has_task_id && has_task_data;
}

Task* deserialize_task(const char* json_str) {
    if (!validate_task_json(json_str)) {
        return NULL;
    }

    struct json_object* obj = json_tokener_parse(json_str);
    Task* task = malloc(sizeof(Task));

    struct json_object* task_id_obj;
    json_object_object_get_ex(obj, "task_id", &task_id_obj);
    task->task_id = strdup(json_object_get_string(task_id_obj));

    struct json_object* task_data_obj;
    json_object_object_get_ex(obj, "task_data", &task_data_obj);
    task->task_data = strdup(json_object_get_string(task_data_obj));

    json_object_put(obj);
    return task;
}

void free_task(Task* task) {
    free(task->task_id);
    free(task->task_data);
    free(task);
}

void process_task(const char* json_str) {
    Task* task = deserialize_task(json_str);
    if (task == NULL) {
        printf("Invalid task data\n");
        return;
    }

    printf("Task ID: %s, Task Data: %s\n", task->task_id, task->task_data);
    free_task(task);
}

int main() {
    const char* json_str = "{\"task_id\":\"task123\",\"task_data\":\"process_data\"}";
    process_task(json_str);
    return 0;
}