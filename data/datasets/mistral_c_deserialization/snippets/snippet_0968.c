#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* task_id;
    char* task_description;
} Task;

void deserialize_task(const char* json_str, Task* task) {
    struct json_object* parsed_json;
    struct json_object* task_id;
    struct json_object* task_description;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "task_id", &task_id);
    json_object_object_get_ex(parsed_json, "task_description", &task_description);

    if (task_id != NULL && json_object_is_type(task_id, json_type_string)) {
        task->task_id = strdup(json_object_get_string(task_id));
    }

    if (task_description != NULL && json_object_is_type(task_description, json_type_string)) {
        task->task_description = strdup(json_object_get_string(task_description));
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"task_id\":\"task123\",\"task_description\":\"Process data\"}";
    Task task;

    deserialize_task(json_str, &task);

    printf("Task ID: %s\n", task.task_id);
    printf("Task Description: %s\n", task.task_description);

    free(task.task_id);
    free(task.task_description);
    return 0;
}