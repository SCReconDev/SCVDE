#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *task_name;
    int priority;
} Task;

void execute_task(Task *task) {
    printf("Executing task: %s\n", task->task_name);
    printf("Priority: %d\n", task->priority);
}

int main() {
    const char *body = "{\"task_name\":\"data_processing\",\"priority\":2}";
    struct json_object *parsed_json;
    struct json_object *task_name;
    struct json_object *priority;
    Task task;

    parsed_json = json_tokener_parse(body);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    json_object_object_get_ex(parsed_json, "task_name", &task_name);
    json_object_object_get_ex(parsed_json, "priority", &priority);

    if (task_name == NULL || priority == NULL) {
        fprintf(stderr, "Missing required fields in JSON\n");
        json_object_put(parsed_json);
        return 1;
    }

    task.task_name = strdup(json_object_get_string(task_name));
    task.priority = json_object_get_int(priority);

    execute_task(&task);

    free(task.task_name);
    json_object_put(parsed_json);

    return 0;
}