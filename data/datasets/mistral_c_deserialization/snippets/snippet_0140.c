#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char task_name[50];
    int priority;
} Task;

void reconstruct_task(Task *task, const char *data) {
    sscanf(data, "%49s %d", task->task_name, &task->priority);
}

void process_background_job(const char *data) {
    Task task;
    reconstruct_task(&task, data);
    printf("Task Name: %s, Priority: %d\n", task.task_name, task.priority);
}

int main() {
    char data[100];
    printf("Enter task data: ");
    fgets(data, sizeof(data), stdin);
    process_background_job(data);
    return 0;
}