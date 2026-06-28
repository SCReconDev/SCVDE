#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_TASK_SIZE 1024

typedef struct {
    char task_id[256];
    int task_priority;
    char task_data[256];
} Task;

void deserialize_task(Task *task, const char *task_data) {
    struct json_object *parsed_json;
    struct json_object *task_id_obj, *task_priority_obj, *task_data_obj;

    parsed_json = json_tokener_parse(task_data);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON task data\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "task_id", &task_id_obj);
    json_object_object_get_ex(parsed_json, "task_priority", &task_priority_obj);
    json_object_object_get_ex(parsed_json, "task_data", &task_data_obj);

    if (task_id_obj != NULL && json_object_is_type(task_id_obj, json_type_string)) {
        strncpy(task->task_id, json_object_get_string(task_id_obj), sizeof(task->task_id) - 1);
    }

    if (task_priority_obj != NULL && json_object_is_type(task_priority_obj, json_type_int)) {
        task->task_priority = json_object_get_int(task_priority_obj);
    }

    if (task_data_obj != NULL && json_object_is_type(task_data_obj, json_type_string)) {
        strncpy(task->task_data, json_object_get_string(task_data_obj), sizeof(task->task_data) - 1);
    }

    json_object_put(parsed_json);
}

int main() {
    Task task;
    char task_data[MAX_TASK_SIZE];

    printf("Enter task data: ");
    fgets(task_data, sizeof(task_data), stdin);

    deserialize_task(&task, task_data);

    printf("Deserialized Task:\n");
    printf("Task ID: %s\n", task.task_id);
    printf("Task Priority: %d\n", task.task_priority);
    printf("Task Data: %s\n", task.task_data);

    return 0;
}