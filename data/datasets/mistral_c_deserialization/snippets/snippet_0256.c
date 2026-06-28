#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* task_name;
    int priority;
} Task;

void deserialize_task(char* data, Task* task) {
    char* token = strtok(data, ";");
    task->task_name = strdup(token);
    token = strtok(NULL, ";");
    task->priority = atoi(token);
}

void process_message(char* body) {
    Task task;
    deserialize_task(body, &task);
    printf("Task: %s, Priority: %d\n", task.task_name, task.priority);
    free(task.task_name);
}

int main() {
    char* body = "Backup;1";
    process_message(body);
    return 0;
}