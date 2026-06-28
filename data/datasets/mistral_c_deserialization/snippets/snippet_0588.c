#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* task_name;
    char* task_data;
} Task;

void deserialize_task(const char* json_str, Task* task) {
    struct json_object* parsed_json;
    struct json_object* name_obj;
    struct json_object* data_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "name", &name_obj);
    json_object_object_get_ex(parsed_json, "data", &data_obj);

    if (name_obj != NULL && json_object_is_type(name_obj, json_type_string)) {
        task->task_name = strdup(json_object_get_string(name_obj));
    }

    if (data_obj != NULL && json_object_is_type(data_obj, json_type_string)) {
        task->task_data = strdup(json_object_get_string(data_obj));
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"name\":\"backup\",\"data\":\"important_files\"}";
    Task task;

    deserialize_task(json_str, &task);

    printf("Task Name: %s\n", task.task_name);
    printf("Task Data: %s\n", task.task_data);

    free(task.task_name);
    free(task.task_data);
    return 0;
}