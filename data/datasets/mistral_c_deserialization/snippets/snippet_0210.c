#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char task_name[50];
    int priority;
} BackgroundTask;

void reconstruct_task(BackgroundTask *task, const char *data) {
    sscanf(data, "%49s %d", task->task_name, &task->priority);
}

void process_background_task(const char *data) {
    BackgroundTask task;
    reconstruct_task(&task, data);
    printf("Background Task: %s, Priority: %d\n", task.task_name, task.priority);
}

int main() {
    char data[100];
    printf("Enter background task data: ");
    fgets(data, sizeof(data), stdin);
    process_background_task(data);
    return 0;
}