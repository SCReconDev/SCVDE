#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* task_name;
    int task_id;
} BackgroundTask;

void process_job(char* task_data) {
    BackgroundTask* task = (BackgroundTask*)malloc(sizeof(BackgroundTask));
    memcpy(task, task_data, sizeof(BackgroundTask));
    printf("Task: %s, ID: %d\n", task->task_name, task->task_id);
    free(task);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s <task_data>\n", argv[0]);
        return 1;
    }
    process_job(argv[1]);
    return 0;
}