#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *task_name;
    char *description;
    int priority;
} Task;

void deserialize_task(const char *json_str, Task *task) {
    struct json_object *parsed_json;
    struct json_object *task_name;
    struct json_object *description;
    struct json_object *priority;

    parsed_json = json_tokener_parse(json_str);
    if (json_object_object_get_ex(parsed_json, "task_name", &task_name)) {
        task->task_name = strdup(json_object_get_string(task_name));
    }
    if (json_object_object_get_ex(parsed_json, "description", &description)) {
        task->description = strdup(json_object_get_string(description));
    }
    if (json_object_object_get_ex(parsed_json, "priority", &priority)) {
        task->priority = json_object_get_int(priority);
    }
    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"task_name\":\"Sample Task\",\"description\":\"This is a sample task description.\",\"priority\":1}";
    Task task;

    deserialize_task(json_str, &task);

    printf("Task Name: %s\n", task.task_name);
    printf("Description: %s\n", task.description);
    printf("Priority: %d\n", task.priority);

    free(task.task_name);
    free(task.description);
    return 0;
}