#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char task[256];
    int priority;
} Task;

void deserialize_task(Task *task, const char *data) {
    sscanf(data, "%255[^;];%d", task->task, &task->priority);
}

void process_job(const char *data) {
    Task task;
    deserialize_task(&task, data);
    printf("Task: %s, Priority: %d\n", task.task, task.priority);
}

int main() {
    char data[512];
    printf("Enter task data: ");
    fgets(data, sizeof(data), stdin);
    process_job(data);
    return 0;
}