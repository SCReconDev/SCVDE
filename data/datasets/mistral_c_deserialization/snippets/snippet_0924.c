#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *task_name;
    int priority;
    char *status;
} Task;

void manage_task(Task *task) {
    printf("Task: %s, Priority: %d, Status: %s\n", task->task_name, task->priority, task->status);
}

int main() {
    const char *json_str = "{\"task_name\":\"Code Review\", \"priority\":1, \"status\":\"Pending\"}";
    struct json_object *parsed_json;
    struct json_object *task_name_obj, *priority_obj, *status_obj;
    Task task;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    if (!json_object_object_get_ex(parsed_json, "task_name", &task_name_obj) ||
        !json_object_object_get_ex(parsed_json, "priority", &priority_obj) ||
        !json_object_object_get_ex(parsed_json, "status", &status_obj)) {
        fprintf(stderr, "Error extracting JSON fields\n");
        json_object_put(parsed_json);
        return 1;
    }

    task.task_name = strdup(json_object_get_string(task_name_obj));
    task.priority = json_object_get_int(priority_obj);
    task.status = strdup(json_object_get_string(status_obj));

    manage_task(&task);

    free(task.task_name);
    free(task.status);
    json_object_put(parsed_json);

    return 0;
}