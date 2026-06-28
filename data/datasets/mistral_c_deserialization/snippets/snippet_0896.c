#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char task[50];
    char deadline[50];
    int priority;
} Task;

int validate_task_schema(json_object *jobj) {
    json_object_object_foreach(jobj, key, val) {
        if (strcmp(key, "task") == 0 && !json_object_is_type(val, json_type_string)) {
            return 0;
        }
        if (strcmp(key, "deadline") == 0 && !json_object_is_type(val, json_type_string)) {
            return 0;
        }
        if (strcmp(key, "priority") == 0 && !json_object_is_type(val, json_type_int)) {
            return 0;
        }
    }
    return 1;
}

Task* deserialize_task(const char *json_str) {
    json_object *jobj = json_tokener_parse(json_str);
    if (!jobj) {
        return NULL;
    }

    if (!validate_task_schema(jobj)) {
        json_object_put(jobj);
        return NULL;
    }

    Task *task = (Task*)malloc(sizeof(Task));
    if (!task) {
        json_object_put(jobj);
        return NULL;
    }

    json_object *jtask = json_object_object_get(jobj, "task");
    json_object *jdeadline = json_object_object_get(jobj, "deadline");
    json_object *jpriority = json_object_object_get(jobj, "priority");

    strcpy(task->task, json_object_get_string(jtask));
    strcpy(task->deadline, json_object_get_string(jdeadline));
    task->priority = json_object_get_int(jpriority);

    json_object_put(jobj);
    return task;
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    printf("Enter JSON string: ");
    fgets(buffer, MAX_BUFFER_SIZE, stdin);

    Task *task = deserialize_task(buffer);
    if (task) {
        printf("Task: %s, Deadline: %s, Priority: %d\n", task->task, task->deadline, task->priority);
        free(task);
    } else {
        printf("Invalid JSON or schema\n");
    }

    return 0;
}