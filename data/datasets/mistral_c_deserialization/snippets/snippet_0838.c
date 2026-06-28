#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* task_name;
    int duration;
} BackgroundTask;

void deserialize_background_task(const char* json_str, BackgroundTask* task) {
    struct json_object* parsed_json;
    struct json_object* task_name;
    struct json_object* duration;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "task_name", &task_name);
    json_object_object_get_ex(parsed_json, "duration", &duration);

    if (task_name != NULL && json_object_get_type(task_name) == json_type_string) {
        task->task_name = strdup(json_object_get_string(task_name));
    }

    if (duration != NULL && json_object_get_type(duration) == json_type_int) {
        task->duration = json_object_get_int(duration);
    }

    json_object_put(parsed_json);
}

void process_background_job(const char* task_data) {
    BackgroundTask task = {NULL, 0};
    deserialize_background_task(task_data, &task);

    if (task.task_name != NULL) {
        printf("Task Name: %s\n", task.task_name);
        free(task.task_name);
    }

    printf("Duration: %d\n", task.duration);
}

int main() {
    const char* task_data = "{\"task_name\":\"backup\",\"duration\":120}";
    process_background_job(task_data);
    return 0;
}