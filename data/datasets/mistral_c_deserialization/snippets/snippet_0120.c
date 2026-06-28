#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* task_name;
    int priority;
} Task;

void process_task(const char* task_data, Task* task) {
    char* data = strdup(task_data);
    char* token = strtok(data, ",");
    task->task_name = strdup(token);
    token = strtok(NULL, ",");
    task->priority = atoi(token);
    free(data);
}

int main() {
    char* task_data = "backup,1";
    Task task;
    process_task(task_data, &task);
    printf("Task Name: %s, Priority: %d\n", task.task_name, task.priority);
    free(task.task_name);
    return 0;
}