#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* task;
    int priority;
} Task;

void deserialize_task(const char* json_str, Task* task) {
    struct json_object* parsed_json;
    struct json_object* task_name;
    struct json_object* priority;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "task", &task_name);
    json_object_object_get_ex(parsed_json, "priority", &priority);

    if (task_name != NULL && json_object_get_type(task_name) == json_type_string) {
        task->task = strdup(json_object_get_string(task_name));
    }

    if (priority != NULL && json_object_get_type(priority) == json_type_int) {
        task->priority = json_object_get_int(priority);
    }

    json_object_put(parsed_json);
}

void process_message(const char* body) {
    Task task = {NULL, 0};
    deserialize_task(body, &task);

    if (task.task != NULL) {
        printf("Task: %s\n", task.task);
        free(task.task);
    }

    printf("Priority: %d\n", task.priority);
}

int main() {
    const char* body = "{\"task\":\"process_data\",\"priority\":1}";
    process_message(body);
    return 0;
}