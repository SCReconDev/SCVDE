#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *task_name;
    char *task_data;
} Task;

void deserialize_task(const char *json_str, Task *task) {
    struct json_object *parsed_json;
    struct json_object *task_name;
    struct json_object *task_data;

    parsed_json = json_tokener_parse(json_str);

    if (json_object_object_get_ex(parsed_json, "task_name", &task_name)) {
        task->task_name = strdup(json_object_get_string(task_name));
    }

    if (json_object_object_get_ex(parsed_json, "task_data", &task_data)) {
        task->task_data = strdup(json_object_get_string(task_data));
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"task_name\":\"process_data\",\"task_data\":\"{\\\"data\\\":\\\"sample\\\"}\"}";
    Task task;

    deserialize_task(json_str, &task);

    printf("Task Name: %s\n", task.task_name);
    printf("Task Data: %s\n", task.task_data);

    free(task.task_name);
    free(task.task_data);

    return 0;
}