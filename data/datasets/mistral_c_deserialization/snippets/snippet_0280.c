#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* task;
    char* data;
} Task;

void process_task(Task* task, const char* serialized) {
    char* token = strtok((char*)serialized, ":");
    task->task = strdup(token);
    token = strtok(NULL, ":");
    task->data = strdup(token);
}

int main() {
    char serialized[100];
    printf("Enter serialized task: ");
    fgets(serialized, sizeof(serialized), stdin);
    serialized[strcspn(serialized, "\n")] = 0;

    Task task;
    process_task(&task, serialized);

    printf("Task: %s, Data: %s\n", task.task, task.data);
    free(task.task);
    free(task.data);
    return 0;
}