#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* task_id;
    char* description;
} Task;

void reconstruct_task(const char* data, Task* task) {
    char* token = strtok((char*)data, ";");
    task->task_id = strdup(token);
    token = strtok(NULL, ";");
    task->description = strdup(token);
}

int main() {
    char* data = "task42;Perform background task";
    Task task;
    reconstruct_task(data, &task);
    printf("Task ID: %s, Description: %s\n", task.task_id, task.task_id);
    free(task.task_id);
    free(task.description);
    return 0;
}