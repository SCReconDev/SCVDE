#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char task_name[MAX_BUFFER_SIZE];
    char task_data[MAX_BUFFER_SIZE];
} BackgroundTask;

void reconstruct_background_task(const char *json_str, BackgroundTask *task) {
    struct json_object *parsed_json;
    struct json_object *task_name_obj;
    struct json_object *task_data_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "task_name", &task_name_obj);
    if (task_name_obj != NULL) {
        strncpy(task->task_name, json_object_get_string(task_name_obj), MAX_BUFFER_SIZE - 1);
    }

    json_object_object_get_ex(parsed_json, "task_data", &task_data_obj);
    if (task_data_obj != NULL) {
        strncpy(task->task_data, json_object_get_string(task_data_obj), MAX_BUFFER_SIZE - 1);
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"task_name\":\"data_processing\",\"task_data\":\"input_file=data.csv\"}";
    BackgroundTask task;

    reconstruct_background_task(json_str, &task);

    printf("Task Name: %s\n", task.task_name);
    printf("Task Data: %s\n", task.task_data);

    return 0;
}