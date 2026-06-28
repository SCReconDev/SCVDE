#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* task_id;
    char* payload;
} Task;

void process_task(Task* task) {
    printf("Task ID: %s, Payload: %s\n", task->task_id, task->payload);
}

int main() {
    const char* incoming_body = "{\"task_id\":\"task123\",\"payload\":\"{\\\"command\\\":\\\"process\\\",\\\"data\\\":\\\"sample\\\"}\"}";
    struct json_object* parsed_json;
    struct json_object* task_id_obj;
    struct json_object* payload_obj;
    Task task;

    parsed_json = json_tokener_parse(incoming_body);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    if (!json_object_object_get_ex(parsed_json, "task_id", &task_id_obj) ||
        !json_object_object_get_ex(parsed_json, "payload", &payload_obj)) {
        fprintf(stderr, "Error extracting JSON fields\n");
        json_object_put(parsed_json);
        return 1;
    }

    task.task_id = strdup(json_object_get_string(task_id_obj));
    task.payload = strdup(json_object_get_string(payload_obj));

    process_task(&task);

    free(task.task_id);
    free(task.payload);
    json_object_put(parsed_json);

    return 0;
}