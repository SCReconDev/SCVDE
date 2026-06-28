#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* task_name;
    int priority;
} Task;

void load_task(Task* task, const char* data) {
    char* token = strtok((char*)data, ",");
    task->task_name = strdup(token);
    token = strtok(NULL, ",");
    task->priority = atoi(token);
}

int main() {
    char* task_data = "backup,1";
    Task task;
    load_task(&task, task_data);
    printf("Task Name: %s, Priority: %d\n", task.task_name, task.priority);
    free(task.task_name);
    return 0;
}