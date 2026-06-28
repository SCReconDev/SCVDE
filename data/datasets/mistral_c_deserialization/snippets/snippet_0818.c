#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* task_name;
    char* task_data;
} TaskData;

void deserialize_task_data(const char* json_str, TaskData* task_data) {
    struct json_object* parsed_json;
    struct json_object* task_name;
    struct json_object* task_data_content;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (json_object_object_get_ex(parsed_json, "task_name", &task_name)) {
        task_data->task_name = strdup(json_object_get_string(task_name));
    }

    if (json_object_object_get_ex(parsed_json, "task_data", &task_data_content)) {
        task_data->task_data = strdup(json_object_get_string(task_data_content));
    }

    json_object_put(parsed_json);
}

void process_task_data(TaskData* task_data) {
    printf("Task Name: %s\n", task_data->task_name);
    printf("Task Data: %s\n", task_data->task_data);
}

int main() {
    const char* json_str = "{\"task_name\":\"data_processing\",\"task_data\":\"process all files\"}";
    TaskData task_data;

    deserialize_task_data(json_str, &task_data);
    process_task_data(&task_data);

    free(task_data.task_name);
    free(task_data.task_data);
    return 0;
}