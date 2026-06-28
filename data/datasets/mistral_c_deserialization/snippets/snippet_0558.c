#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* task_id;
    char* task_data;
} BackgroundTask;

void parse_task_data(const char* data) {
    struct json_object* parsed_json;
    struct json_object* task_id;
    struct json_object* task_data;

    parsed_json = json_tokener_parse(data);

    if (json_object_object_get_ex(parsed_json, "task_id", &task_id)) {
        BackgroundTask* task = (BackgroundTask*)malloc(sizeof(BackgroundTask));
        task->task_id = strdup(json_object_get_string(task_id));

        if (json_object_object_get_ex(parsed_json, "task_data", &task_data)) {
            task->task_data = strdup(json_object_get_string(task_data));
        } else {
            task->task_data = strdup("");
        }

        printf("Task ID: %s, Task Data: %s\n", task->task_id, task->task_data);
        free(task->task_id);
        free(task->task_data);
        free(task);
    }

    json_object_put(parsed_json);
}

int main() {
    const char* data = "{\"task_id\":\"task123\",\"task_data\":\"Process data\"}";
    parse_task_data(data);
    return 0;
}