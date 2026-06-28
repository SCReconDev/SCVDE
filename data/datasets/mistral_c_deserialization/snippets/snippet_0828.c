#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *task_id;
    char *description;
} Task;

void parse_task(json_object *jobj, Task *task) {
    json_object_object_foreach(jobj, key, val) {
        if (strcmp(key, "task_id") == 0) {
            task->task_id = strdup(json_object_get_string(val));
        } else if (strcmp(key, "description") == 0) {
            task->description = strdup(json_object_get_string(val));
        }
    }
}

int main() {
    const char *task_data = "{\"task_id\":\"task123\",\"description\":\"Process data\"}";
    json_object *jobj = json_tokener_parse(task_data);

    if (jobj == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    Task task;
    parse_task(jobj, &task);

    printf("Task ID: %s\n", task.task_id);
    printf("Description: %s\n", task.description);

    free(task.task_id);
    free(task.description);
    json_object_put(jobj);

    return 0;
}