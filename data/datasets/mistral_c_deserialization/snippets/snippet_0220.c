#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char task_name[50];
    int task_id;
} BackgroundTask;

void process_job(char* task_data) {
    BackgroundTask* task = (BackgroundTask*)malloc(sizeof(BackgroundTask));
    memcpy(task, task_data, sizeof(BackgroundTask));
    printf("Background task processed: %s (ID: %d)\n", task->task_name, task->task_id);
    free(task);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <serialized_task_data>\n", argv[0]);
        return 1;
    }

    char* task_data = argv[1];
    process_job(task_data);

    return 0;
}