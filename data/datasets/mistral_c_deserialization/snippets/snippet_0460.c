#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char task_name[50];
    char task_data[200];
} BackgroundTask;

void deserialize_task(char* data, BackgroundTask* task) {
    char* token = strtok(data, ":");
    strcpy(task->task_name, token);
    token = strtok(NULL, ":");
    strcpy(task->task_data, token);
}

void process_background_task(char* task_data) {
    BackgroundTask task;
    deserialize_task(task_data, &task);
    printf("Processing background task: %s, data: %s\n", task.task_name, task.task_data);
}

int main() {
    char task_data[] = "backup:important files";
    process_background_task(task_data);
    return 0;
}