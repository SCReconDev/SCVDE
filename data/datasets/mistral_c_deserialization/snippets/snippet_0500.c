#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* task_name;
    char* task_data;
} Task;

void reconstruct_task(const char* serialized_data, Task* task) {
    char* token = strtok((char*)serialized_data, "=");
    task->task_name = strdup(token);
    token = strtok(NULL, "=");
    task->task_data = strdup(token);
}

void process_task(const char* task_data) {
    Task task;
    reconstruct_task(task_data, &task);
    printf("Task Name: %s, Task Data: %s\n", task.task_name, task.task_data);
    free(task.task_name);
    free(task.task_data);
}

int main() {
    const char* task_data = "backup_task=dark_mode=true";
    process_task(task_data);
    return 0;
}