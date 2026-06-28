#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* task;
    char* data;
} Task;

void reconstruct_task(Task* task, const char* data) {
    char* token = strtok((char*)data, "#");
    task->task = strdup(token);
    token = strtok(NULL, "#");
    task->data = strdup(token);
}

int main() {
    char task_data[] = "process#data123";
    Task task;
    reconstruct_task(&task, task_data);

    printf("Task: %s, Data: %s\n", task.task, task.data);

    free(task.task);
    free(task.data);
    return 0;
}