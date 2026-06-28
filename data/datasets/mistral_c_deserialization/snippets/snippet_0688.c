#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_TASK_SIZE 1024

typedef struct {
    char task_name[50];
    int priority;
} Task;

int validate_task(json_object *jobj) {
    json_object *jtask_name, *jpriority;

    if (!json_object_object_get_ex(jobj, "task_name", &jtask_name) ||
        !json_object_object_get_ex(jobj, "priority", &jpriority)) {
        return 0;
    }

    if (json_object_get_type(jtask_name) != json_type_string ||
        json_object_get_type(jpriority) != json_type_int) {
        return 0;
    }

    return 1;
}

Task* reconstruct_task(const char *task_data) {
    json_object *jobj = json_tokener_parse(task_data);
    if (jobj == NULL) {
        return NULL;
    }

    if (!validate_task(jobj)) {
        json_object_put(jobj);
        return NULL;
    }

    Task *task = (Task*)malloc(sizeof(Task));
    if (task == NULL) {
        json_object_put(jobj);
        return NULL;
    }

    strcpy(task->task_name, json_object_get_string(json_object_object_get(jobj, "task_name")));
    task->priority = json_object_get_int(json_object_object_get(jobj, "priority"));

    json_object_put(jobj);
    return task;
}

int main() {
    char task_data[MAX_TASK_SIZE];
    printf("Enter task data: ");
    fgets(task_data, MAX_TASK_SIZE, stdin);

    Task *task = reconstruct_task(task_data);
    if (task != NULL) {
        printf("Task Name: %s\nPriority: %d\n", task->task_name, task->priority);
        free(task);
    } else {
        printf("Invalid task data.\n");
    }

    return 0;
}