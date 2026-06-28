#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* task_name;
    int task_id;
} BackgroundTask;

void deserialize_task(char* data, BackgroundTask* task) {
    char* token = strtok(data, "-");
    task->task_name = strdup(token);
    token = strtok(NULL, "-");
    task->task_id = atoi(token);
}

void process_job(char* task_data) {
    BackgroundTask task;
    deserialize_task(task_data, &task);
    printf("Task: %s, ID: %d\n", task.task_name, task.task_id);
    free(task.task_name);
}

int main() {
    char* task_data = "backup-123";
    process_job(task_data);
    return 0;
}