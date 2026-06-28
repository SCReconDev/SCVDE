#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <json-c/json.h>

typedef struct {
    char *task_id;
    char *description;
    bool completed;
} Task;

bool validate_task_schema(const json_object *jobj) {
    json_object_object_foreach(jobj, key, val) {
        if (strcmp(key, "task_id") == 0 && json_object_get_type(val) != json_type_string) {
            return false;
        }
        if (strcmp(key, "description") == 0 && json_object_get_type(val) != json_type_string) {
            return false;
        }
        if (strcmp(key, "completed") == 0 && json_object_get_type(val) != json_type_boolean) {
            return false;
        }
    }
    return true;
}

Task *deserialize_task(const char *json_str) {
    json_object *jobj = json_tokener_parse(json_str);
    if (!jobj) {
        return NULL;
    }

    if (!validate_task_schema(jobj)) {
        json_object_put(jobj);
        return NULL;
    }

    Task *task = malloc(sizeof(Task));
    if (!task) {
        json_object_put(jobj);
        return NULL;
    }

    json_object *task_id_obj, *description_obj, *completed_obj;
    if (json_object_object_get_ex(jobj, "task_id", &task_id_obj)) {
        task->task_id = strdup(json_object_get_string(task_id_obj));
    } else {
        task->task_id = NULL;
    }

    if (json_object_object_get_ex(jobj, "description", &description_obj)) {
        task->description = strdup(json_object_get_string(description_obj));
    } else {
        task->description = NULL;
    }

    if (json_object_object_get_ex(jobj, "completed", &completed_obj)) {
        task->completed = json_object_get_boolean(completed_obj);
    } else {
        task->completed = false;
    }

    json_object_put(jobj);
    return task;
}

void free_task(Task *task) {
    if (task) {
        free(task->task_id);
        free(task->description);
        free(task);
    }
}

int main() {
    const char *json_str = "{\"task_id\":\"67890\",\"description\":\"Complete project\",\"completed\":false}";
    Task *task = deserialize_task(json_str);

    if (task) {
        printf("Task ID: %s\n", task->task_id);
        printf("Description: %s\n", task->description);
        printf("Completed: %s\n", task->completed ? "Yes" : "No");
        free_task(task);
    } else {
        printf("Failed to deserialize task.\n");
    }

    return 0;
}