#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* task_name;
    int status;
} BackgroundTask;

void deserialize_background_task(BackgroundTask* task, const char* data) {
    char* token = strtok((char*)data, ":");
    task->task_name = strdup(token);
    token = strtok(NULL, ":");
    task->status = atoi(token);
}

void process_background_job(const char* task_data) {
    BackgroundTask task;
    deserialize_background_task(&task, task_data);
    printf("Background Task - Name: %s, Status: %d\n", task.task_name, task.status);
    free(task.task_name);
}

int main() {
    const char* task_data = "data_processing:1";
    process_background_job(task_data);
    return 0;
}