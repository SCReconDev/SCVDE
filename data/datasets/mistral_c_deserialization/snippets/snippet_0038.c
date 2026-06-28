#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* task_name;
    int priority;
} Task;

void reconstruct_task(Task* task, const char* data) {
    char* token = strtok((char*)data, "-");
    task->task_name = strdup(token);
    token = strtok(NULL, "-");
    task->priority = atoi(token);
}

int main() {
    char* data = "backup-3";
    Task task;
    reconstruct_task(&task, data);
    printf("Task Name: %s, Priority: %d\n", task.task_name, task.priority);
    free(task.task_name);
    return 0;
}