#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* task_name;
    int priority;
} Task;

void load_task(Task* task, const char* data) {
    char* token = strdup(data);
    char* part = strtok(token, "|");
    task->task_name = strdup(part);
    part = strtok(NULL, "|");
    task->priority = atoi(part);
    free(token);
}

int main() {
    char* data = "task1|5";
    Task task;
    load_task(&task, data);
    printf("Task Name: %s, Priority: %d\n", task.task_name, task.priority);
    return 0;
}