#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* task_name;
    int priority;
    char* description;
} Task;

void show_task(Task* task) {
    printf("Task Name: %s\n", task->task_name);
    printf("Priority: %d\n", task->priority);
    printf("Description: %s\n", task->description);
}

int main() {
    const char* json_str = "{\"task_name\":\"Code Review\",\"priority\":2,\"description\":\"Review the new code changes\"}";
    struct json_object* parsed_json;
    struct json_object* task_name;
    struct json_object* priority;
    struct json_object* description;
    Task task;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    json_object_object_get_ex(parsed_json, "task_name", &task_name);
    json_object_object_get_ex(parsed_json, "priority", &priority);
    json_object_object_get_ex(parsed_json, "description", &description);

    if (task_name == NULL || priority == NULL || description == NULL) {
        fprintf(stderr, "Invalid JSON structure\n");
        json_object_put(parsed_json);
        return 1;
    }

    task.task_name = strdup(json_object_get_string(task_name));
    task.priority = json_object_get_int(priority);
    task.description = strdup(json_object_get_string(description));

    show_task(&task);

    free(task.task_name);
    free(task.description);
    json_object_put(parsed_json);

    return 0;
}