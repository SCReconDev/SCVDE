#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_INPUT_SIZE 1024

typedef struct {
    char task_id[256];
    char task_name[256];
    char task_data[256];
} Task;

int validate_task(Task *task) {
    if (strlen(task->task_id) == 0 || strlen(task->task_name) == 0 || strlen(task->task_data) == 0) {
        return 0;
    }
    return 1;
}

Task* deserialize_task(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *task_id_obj, *task_name_obj, *task_data_obj;
    Task *task = malloc(sizeof(Task));

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        free(task);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "task_id", &task_id_obj);
    json_object_object_get_ex(parsed_json, "task_name", &task_name_obj);
    json_object_object_get_ex(parsed_json, "task_data", &task_data_obj);

    if (task_id_obj == NULL || task_name_obj == NULL || task_data_obj == NULL) {
        json_object_put(parsed_json);
        free(task);
        return NULL;
    }

    strncpy(task->task_id, json_object_get_string(task_id_obj), sizeof(task->task_id) - 1);
    strncpy(task->task_name, json_object_get_string(task_name_obj), sizeof(task->task_name) - 1);
    strncpy(task->task_data, json_object_get_string(task_data_obj), sizeof(task->task_data) - 1);

    json_object_put(parsed_json);

    if (!validate_task(task)) {
        free(task);
        return NULL;
    }

    return task;
}

void process_task(Task *task) {
    printf("Processing task: %s, %s, %s\n", task->task_id, task->task_name, task->task_data);
}

int main() {
    char input[MAX_INPUT_SIZE];
    Task *task;

    printf("Enter task data in JSON format: ");
    fgets(input, sizeof(input), stdin);

    task = deserialize_task(input);
    if (task == NULL) {
        printf("Invalid task data\n");
        return 1;
    }

    process_task(task);

    free(task);
    return 0;
}