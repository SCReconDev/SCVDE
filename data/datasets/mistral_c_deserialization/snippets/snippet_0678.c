#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* task_id;
    char* description;
} TaskData;

void process_task(TaskData* task) {
    printf("Task ID: %s, Description: %s\n", task->task_id, task->description);
}

int main() {
    const char* task_data = "{\"task_id\":\"task1\",\"description\":\"Process data\"}";
    struct json_object* json_obj = json_tokener_parse(task_data);

    if (json_obj == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    TaskData task;
    json_object_object_foreach(json_obj, key, val) {
        if (strcmp(key, "task_id") == 0) {
            task.task_id = strdup(json_object_get_string(val));
        } else if (strcmp(key, "description") == 0) {
            task.description = strdup(json_object_get_string(val));
        }
    }

    process_task(&task);
    free(task.task_id);
    free(task.description);
    json_object_put(json_obj);

    return 0;
}