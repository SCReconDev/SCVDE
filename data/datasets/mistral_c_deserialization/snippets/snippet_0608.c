#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* task_id;
    char* task_data;
} Task;

void process_task(Task* task) {
    printf("Task ID: %s\n", task->task_id);
    printf("Task Data: %s\n", task->task_data);
}

Task* deserialize_task(const char* json_str) {
    struct json_object* parsed_json;
    struct json_object* task_id_obj;
    struct json_object* task_data_obj;
    Task* task = malloc(sizeof(Task));

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        free(task);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "task_id", &task_id_obj);
    json_object_object_get_ex(parsed_json, "task_data", &task_data_obj);

    if (task_id_obj == NULL || task_data_obj == NULL) {
        fprintf(stderr, "Invalid JSON format\n");
        json_object_put(parsed_json);
        free(task);
        return NULL;
    }

    task->task_id = strdup(json_object_get_string(task_id_obj));
    task->task_data = strdup(json_object_get_string(task_data_obj));

    json_object_put(parsed_json);
    return task;
}

int main() {
    const char* json_str = "{\"task_id\":\"task123\",\"task_data\":\"process_data\"}";
    Task* task = deserialize_task(json_str);

    if (task != NULL) {
        process_task(task);
        free(task->task_id);
        free(task->task_data);
        free(task);
    }

    return 0;
}