#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char task_id[50];
    char task_name[50];
    char task_data[100];
} TaskInfo;

int validate_task_info(TaskInfo *task_info) {
    if (strlen(task_info->task_id) == 0 || strlen(task_info->task_name) == 0 || strlen(task_info->task_data) == 0) {
        return 0;
    }
    return 1;
}

TaskInfo* deserialize_task_info(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *task_id_obj, *task_name_obj, *task_data_obj;
    TaskInfo *task_info = (TaskInfo*)malloc(sizeof(TaskInfo));

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        free(task_info);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "task_id", &task_id_obj);
    json_object_object_get_ex(parsed_json, "task_name", &task_name_obj);
    json_object_object_get_ex(parsed_json, "task_data", &task_data_obj);

    if (task_id_obj == NULL || task_name_obj == NULL || task_data_obj == NULL) {
        json_object_put(parsed_json);
        free(task_info);
        return NULL;
    }

    strncpy(task_info->task_id, json_object_get_string(task_id_obj), sizeof(task_info->task_id) - 1);
    strncpy(task_info->task_name, json_object_get_string(task_name_obj), sizeof(task_info->task_name) - 1);
    strncpy(task_info->task_data, json_object_get_string(task_data_obj), sizeof(task_info->task_data) - 1);

    json_object_put(parsed_json);

    if (!validate_task_info(task_info)) {
        free(task_info);
        return NULL;
    }

    return task_info;
}

void process_task_info(TaskInfo *task_info) {
    printf("Task ID: %s\n", task_info->task_id);
    printf("Task Name: %s\n", task_info->task_name);
    printf("Task Data: %s\n", task_info->task_data);
}

int main() {
    char json_str[MAX_BUFFER_SIZE];
    TaskInfo *task_info;

    printf("Enter task info data in JSON format:\n");
    fgets(json_str, MAX_BUFFER_SIZE, stdin);

    task_info = deserialize_task_info(json_str);
    if (task_info == NULL) {
        printf("Invalid task info data\n");
        return 1;
    }

    process_task_info(task_info);
    free(task_info);

    return 0;
}