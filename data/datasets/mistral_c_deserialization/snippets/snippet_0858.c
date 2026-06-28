#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char task_name[50];
    int priority;
} Task;

int deserialize_task(const char* json_str, Task* task) {
    struct json_object *parsed_json;
    struct json_object *task_name_obj, *priority_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return -1;
    }

    if (!json_object_object_get_ex(parsed_json, "task_name", &task_name_obj)) {
        fprintf(stderr, "Error getting task_name\n");
        json_object_put(parsed_json);
        return -1;
    }

    if (!json_object_object_get_ex(parsed_json, "priority", &priority_obj)) {
        fprintf(stderr, "Error getting priority\n");
        json_object_put(parsed_json);
        return -1;
    }

    strncpy(task->task_name, json_object_get_string(task_name_obj), sizeof(task->task_name) - 1);
    task->priority = json_object_get_int(priority_obj);

    json_object_put(parsed_json);
    return 0;
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    Task task;

    printf("Enter task JSON: ");
    fgets(buffer, sizeof(buffer), stdin);

    if (deserialize_task(buffer, &task) == 0) {
        printf("Deserialized Task: Name=%s, Priority=%d\n", task.task_name, task.priority);
    } else {
        fprintf(stderr, "Failed to deserialize task\n");
    }

    return 0;
}