#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* task_name;
    int duration;
} BackgroundTask;

void process_background_task(BackgroundTask* task) {
    printf("Task Name: %s\n", task->task_name);
    printf("Duration: %d\n", task->duration);
}

void deserialize_background_task(const char* data, BackgroundTask* task) {
    char* token = strtok((char*)data, ";");
    task->task_name = strdup(token);
    token = strtok(NULL, ";");
    task->duration = atoi(token);
}

void process_background_job(const char* data) {
    BackgroundTask task;
    deserialize_background_task(data, &task);
    process_background_task(&task);
}

int main() {
    const char* data = "DataProcessing;3600";
    process_background_job(data);
    return 0;
}