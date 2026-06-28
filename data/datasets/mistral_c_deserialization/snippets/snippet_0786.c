#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *task_id;
    char *status;
} Task;

void deserialize_task(const char *json_str, Task *task) {
    struct json_object *parsed_json;
    struct json_object *task_id_obj, *status_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "task_id", &task_id_obj) ||
        !json_object_object_get_ex(parsed_json, "status", &status_obj)) {
        fprintf(stderr, "Error: Missing required fields\n");
        json_object_put(parsed_json);
        return;
    }

    if (json_object_get_type(task_id_obj) != json_type_string ||
        json_object_get_type(status_obj) != json_type_string) {
        fprintf(stderr, "Error: Invalid field types\n");
        json_object_put(parsed_json);
        return;
    }

    task->task_id = strdup(json_object_get_string(task_id_obj));
    task->status = strdup(json_object_get_string(status_obj));

    json_object_put(parsed_json);
}

void process_task(Task *task) {
    printf("Task ID: %s\n", task->task_id);
    printf("Status: %s\n", task->status);
}

int main() {
    const char *json_str = "{\"task_id\": \"67890\", \"status\": \"completed\"}";
    Task task;

    deserialize_task(json_str, &task);
    process_task(&task);

    free(task.task_id);
    free(task.status);
    return 0;
}