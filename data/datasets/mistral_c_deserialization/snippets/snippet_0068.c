#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* task_type;
    char* task_data;
} BackgroundTask;

void reconstruct_task(const char* data, BackgroundTask* task) {
    char* token = strtok((char*)data, ",");
    task->task_type = strdup(token);
    token = strtok(NULL, ",");
    task->task_data = strdup(token);
}

void process_background_job(const char* data) {
    BackgroundTask task;
    reconstruct_task(data, &task);
    printf("Task Type: %s, Task Data: %s\n", task.task_type, task.task_data);
    free(task.task_type);
    free(task.task_data);
}

int main() {
    const char* data = "data_processing,large_dataset";
    process_background_job(data);
    return 0;
}