#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* task_name;
    int priority;
} Task;

void execute_task(const char* data) {
    Task task;
    char* decoded = strdup(data);
    char* token = strtok(decoded, "|");
    task.task_name = strdup(token);
    token = strtok(NULL, "|");
    task.priority = atoi(token);
    printf("Executing task: %s (Priority: %d)\n", task.task_name, task.priority);
    free(task.task_name);
    free(decoded);
}

int main() {
    const char* data = "backup_data|3";
    execute_task(data);
    return 0;
}