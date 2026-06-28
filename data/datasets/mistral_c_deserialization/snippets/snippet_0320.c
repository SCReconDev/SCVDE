#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* task_name;
    int priority;
    char* data;
} Task;

void process_task(const char* data, Task* task) {
    char* token = strtok((char*)data, ":");
    task->task_name = strdup(token);
    token = strtok(NULL, ":");
    task->priority = atoi(token);
    token = strtok(NULL, ":");
    task->data = strdup(token);
}

int main() {
    char* task_data = "data_processing:1:{input: file.csv, output: result.json}";
    Task task;
    process_task(task_data, &task);
    printf("Task Name: %s, Priority: %d, Data: %s\n", task.task_name, task.priority, task.data);
    free(task.task_name);
    free(task.data);
    return 0;
}