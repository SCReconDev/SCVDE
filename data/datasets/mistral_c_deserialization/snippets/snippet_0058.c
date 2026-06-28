#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* task_name;
    int priority;
} Task;

void deserialize_task(const char* data, Task* task) {
    char* token = strtok((char*)data, ":");
    task->task_name = strdup(token);

    token = strtok(NULL, ":");
    task->priority = atoi(token);
}

int main() {
    const char* data = "backup:1";
    Task task;

    deserialize_task(data, &task);

    printf("Task Name: %s, Priority: %d\n", task.task_name, task.priority);

    free(task.task_name);
    return 0;
}