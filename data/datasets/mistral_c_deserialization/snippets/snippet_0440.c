#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* task_name;
    char* task_data;
} BackgroundTask;

void process_task(BackgroundTask* task) {
    printf("Processing task: %s, Data: %s\n", task->task_name, task->task_data);
}

int main() {
    char* task_data = "{\"task_name\":\"backup\",\"task_data\":\"full\"}";
    BackgroundTask* task = (BackgroundTask*)malloc(sizeof(BackgroundTask));
    memcpy(task, task_data, sizeof(BackgroundTask));
    process_task(task);
    free(task);
    return 0;
}