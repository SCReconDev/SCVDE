#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* task_id;
    char* description;
} Task;

void load_task(const char* json_str, Task* task) {
    struct json_object* parsed_json;
    struct json_object* task_id;
    struct json_object* description;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "task_id", &task_id)) {
        fprintf(stderr, "Error: 'task_id' field not found\n");
        json_object_put(parsed_json);
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "description", &description)) {
        fprintf(stderr, "Error: 'description' field not found\n");
        json_object_put(parsed_json);
        return;
    }

    task->task_id = strdup(json_object_get_string(task_id));
    task->description = strdup(json_object_get_string(description));

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"task_id\":\"task123\",\"description\":\"Process data\"}";
    Task task;

    load_task(json_str, &task);

    printf("Task ID: %s\n", task.task_id);
    printf("Description: %s\n", task.description);

    free(task.task_id);
    free(task.description);
    return 0;
}