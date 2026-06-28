#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *task_id;
    char *task_description;
} Task;

void process_task(const char *task_data, Task *task) {
    struct json_object *parsed_json;
    struct json_object *task_id_obj;
    struct json_object *task_description_obj;

    parsed_json = json_tokener_parse(task_data);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (json_object_object_get_ex(parsed_json, "task_id", &task_id_obj)) {
        task->task_id = strdup(json_object_get_string(task_id_obj));
    }

    if (json_object_object_get_ex(parsed_json, "task_description", &task_description_obj)) {
        task->task_description = strdup(json_object_get_string(task_description_obj));
    }

    json_object_put(parsed_json);
}

int main() {
    const char *task_data = "{\"task_id\":\"task123\",\"task_description\":\"Process data\"}";
    Task task;

    process_task(task_data, &task);

    printf("Task ID: %s\n", task.task_id);
    printf("Task Description: %s\n", task.task_description);

    free(task.task_id);
    free(task.task_description);
    return 0;
}