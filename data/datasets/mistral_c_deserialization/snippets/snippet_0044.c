#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* task_name;
    int priority;
} Task;

void process_task(Task* task) {
    printf("Task Name: %s\n", task->task_name);
    printf("Priority: %d\n", task->priority);
}

void deserialize_task(const char* body, Task* task) {
    char* data = strdup(body);
    char* token = strtok(data, ",");
    task->task_name = strdup(token);
    token = strtok(NULL, ",");
    task->priority = atoi(token);
    free(data);
}

void process_message(const char* body) {
    Task task;
    deserialize_task(body, &task);
    process_task(&task);
}

int main() {
    const char* body = "Backup,3";
    process_message(body);
    return 0;
}