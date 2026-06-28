#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char task_name[50];
    char task_data[100];
} BackgroundTask;

void reconstruct_task(const char* data, BackgroundTask* task) {
    char* task_data = strdup(data);
    char* token = strtok(task_data, ":");
    strcpy(task->task_name, token);
    token = strtok(NULL, ":");
    strcpy(task->task_data, token);
    free(task_data);
}

int main() {
    char* data = "data_processing:input_file.csv";
    BackgroundTask task;
    reconstruct_task(data, &task);
    printf("Task Name: %s, Task Data: %s\n", task.task_name, task.task_data);
    return 0;
}