#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *task_name;
    int duration;
} Task;

void deserialize_task(const char *json_str, Task *task) {
    struct json_object *parsed_json;
    struct json_object *task_name;
    struct json_object *duration;

    parsed_json = json_tokener_parse(json_str);

    if (json_object_object_get_ex(parsed_json, "task_name", &task_name)) {
        task->task_name = strdup(json_object_get_string(task_name));
    }

    if (json_object_object_get_ex(parsed_json, "duration", &duration)) {
        task->duration = json_object_get_int(duration);
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"task_name\":\"backup\",\"duration\":3600}";
    Task task;

    deserialize_task(json_str, &task);

    printf("Task Name: %s\n", task.task_name);
    printf("Duration: %d\n", task.duration);

    free(task.task_name);

    return 0;
}