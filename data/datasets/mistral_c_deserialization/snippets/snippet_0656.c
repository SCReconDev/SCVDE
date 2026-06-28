#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *task_name;
    char *description;
    int priority;
} Task;

void deserialize_task(const char *json_str, Task *task) {
    struct json_object *parsed_json;
    struct json_object *name_obj, *desc_obj, *priority_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "task_name", &name_obj);
    json_object_object_get_ex(parsed_json, "description", &desc_obj);
    json_object_object_get_ex(parsed_json, "priority", &priority_obj);

    if (name_obj != NULL && json_object_get_type(name_obj) == json_type_string) {
        task->task_name = strdup(json_object_get_string(name_obj));
    }

    if (desc_obj != NULL && json_object_get_type(desc_obj) == json_type_string) {
        task->description = strdup(json_object_get_string(desc_obj));
    }

    if (priority_obj != NULL && json_object_get_type(priority_obj) == json_type_int) {
        task->priority = json_object_get_int(priority_obj);
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"task_name\":\"Code Review\",\"description\":\"Review the latest code changes\",\"priority\":2}";
    Task task;

    deserialize_task(json_str, &task);

    printf("Task Name: %s\n", task.task_name);
    printf("Description: %s\n", task.description);
    printf("Priority: %d\n", task.priority);

    free(task.task_name);
    free(task.description);
    return 0;
}