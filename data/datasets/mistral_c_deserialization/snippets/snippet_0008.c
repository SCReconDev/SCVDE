#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char task_name[50];
    int task_priority;
} Task;

void reconstruct_task(Task *task, const char *data) {
    sscanf(data, "%49s %d", task->task_name, &task->task_priority);
}

void process_task(const char *data) {
    Task task;
    reconstruct_task(&task, data);
    printf("Task Name: %s, Task Priority: %d\n", task.task_name, task.task_priority);
}

int main() {
    char data[100];
    printf("Enter data: ");
    fgets(data, sizeof(data), stdin);
    process_task(data);
    return 0;
}