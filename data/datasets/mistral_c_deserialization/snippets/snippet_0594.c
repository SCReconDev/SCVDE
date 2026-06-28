#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *task_id;
    char *description;
    int priority;
} Task;

void parse_task_data(const char *json_str, Task *task) {
    struct json_object *parsed_json;
    struct json_object *id_obj;
    struct json_object *desc_obj;
    struct json_object *priority_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (json_object_object_get_ex(parsed_json, "task_id", &id_obj)) {
        task->task_id = strdup(json_object_get_string(id_obj));
    }

    if (json_object_object_get_ex(parsed_json, "description", &desc_obj)) {
        task->description = strdup(json_object_get_string(desc_obj));
    }

    if (json_object_object_get_ex(parsed_json, "priority", &priority_obj)) {
        task->priority = json_object_get_int(priority_obj);
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"task_id\":\"T123\",\"description\":\"Complete project\",\"priority\":1}";
    Task task;

    parse_task_data(json_str, &task);

    printf("Task ID: %s\n", task.task_id);
    printf("Description: %s\n", task.description);
    printf("Priority: %d\n", task.priority);

    free(task.task_id);
    free(task.description);
    return 0;
}