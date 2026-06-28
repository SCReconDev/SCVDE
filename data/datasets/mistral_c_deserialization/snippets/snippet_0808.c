#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *task_id;
    char *task_data;
} TaskData;

void deserialize_task_data(const char *json_str, TaskData *task_data) {
    struct json_object *parsed_json;
    struct json_object *task_id_obj, *task_data_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "task_id", &task_id_obj);
    json_object_object_get_ex(parsed_json, "task_data", &task_data_obj);

    if (task_id_obj != NULL && json_object_get_type(task_id_obj) == json_type_string) {
        task_data->task_id = strdup(json_object_get_string(task_id_obj));
    }

    if (task_data_obj != NULL && json_object_get_type(task_data_obj) == json_type_string) {
        task_data->task_data = strdup(json_object_get_string(task_data_obj));
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"task_id\":\"task123\",\"task_data\":\"process_data\"}";
    TaskData task_data;

    deserialize_task_data(json_str, &task_data);

    printf("Task ID: %s\n", task_data.task_id);
    printf("Task Data: %s\n", task_data.task_data);

    free(task_data.task_id);
    free(task_data.task_data);
    return 0;
}