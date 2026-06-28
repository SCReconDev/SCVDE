#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *task_id;
    char *payload;
} Task;

void parse_task(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *task_id;
    struct json_object *payload;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "task_id", &task_id)) {
        fprintf(stderr, "Task ID not found in JSON\n");
        json_object_put(parsed_json);
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "payload", &payload)) {
        fprintf(stderr, "Payload not found in JSON\n");
        json_object_put(parsed_json);
        return;
    }

    Task task;
    task.task_id = strdup(json_object_get_string(task_id));
    task.payload = strdup(json_object_get_string(payload));

    printf("Task ID: %s, Payload: %s\n", task.task_id, task.payload);

    free(task.task_id);
    free(task.payload);
    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"task_id\":\"123\",\"payload\":\"process_data\"}";
    parse_task(json_str);
    return 0;
}