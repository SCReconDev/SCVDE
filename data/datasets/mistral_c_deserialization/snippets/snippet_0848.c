#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_TASK_SIZE 2048

typedef struct {
    char task_name[50];
    int priority;
} Task;

void process_task_data(const char *task_data) {
    struct json_object *parsed_json;
    struct json_object *name_obj, *priority_obj;
    Task task;

    parsed_json = json_tokener_parse(task_data);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing task data\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "name", &name_obj) ||
        !json_object_object_get_ex(parsed_json, "priority", &priority_obj)) {
        fprintf(stderr, "Invalid task format\n");
        json_object_put(parsed_json);
        return;
    }

    strncpy(task.task_name, json_object_get_string(name_obj), sizeof(task.task_name) - 1);
    task.priority = json_object_get_int(priority_obj);

    printf("Task Name: %s\n", task.task_name);
    printf("Priority: %d\n", task.priority);

    json_object_put(parsed_json);
}

int main() {
    char task[MAX_TASK_SIZE];
    printf("Enter task data: ");
    fgets(task, sizeof(task), stdin);

    process_task_data(task);

    return 0;
}