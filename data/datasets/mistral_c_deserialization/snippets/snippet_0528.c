#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char task_name[MAX_BUFFER_SIZE];
    char task_data[MAX_BUFFER_SIZE];
} Task;

void process_background_task(const char* json_data) {
    struct json_object *parsed_json;
    struct json_object *task_name_obj, *task_data_obj;
    Task task;

    parsed_json = json_tokener_parse(json_data);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON data\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "task_name", &task_name_obj) ||
        !json_object_object_get_ex(parsed_json, "task_data", &task_data_obj)) {
        fprintf(stderr, "Error: Missing required fields in JSON data\n");
        json_object_put(parsed_json);
        return;
    }

    strncpy(task.task_name, json_object_get_string(task_name_obj), MAX_BUFFER_SIZE - 1);
    strncpy(task.task_data, json_object_get_string(task_data_obj), MAX_BUFFER_SIZE - 1);

    printf("Task Name: %s, Task Data: %s\n", task.task_name, task.task_data);

    json_object_put(parsed_json);
}

int main() {
    const char* json_data = "{\"task_name\":\"backup\",\"task_data\":\"backup_data\"}";
    process_background_task(json_data);
    return 0;
}