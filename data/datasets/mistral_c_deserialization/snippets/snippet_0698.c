#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* task_id;
    char* task_data;
} Task;

void deserialize_task(const char* json_str, Task* task) {
    struct json_object* parsed_json;
    struct json_object* task_id;
    struct json_object* task_data;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (json_object_object_get_ex(parsed_json, "task_id", &task_id)) {
        task->task_id = strdup(json_object_get_string(task_id));
    }

    if (json_object_object_get_ex(parsed_json, "task_data", &task_data)) {
        task->task_data = strdup(json_object_get_string(task_data));
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"task_id\":\"task123\",\"task_data\":\"Process data\"}";
    Task task;

    deserialize_task(json_str, &task);

    printf("Task ID: %s\n", task.task_id);
    printf("Task Data: %s\n", task.task_data);

    free(task.task_id);
    free(task.task_data);
    return 0;
}