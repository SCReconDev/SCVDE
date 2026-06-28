#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char task_name[50];
    char task_data[100];
} Task;

void reconstruct_task(Task *task, const char *data) {
    char *token = strtok((char *)data, "-");
    if (token != NULL) {
        strncpy(task->task_name, token, sizeof(task->task_name) - 1);
        token = strtok(NULL, "-");
        if (token != NULL) {
            strncpy(task->task_data, token, sizeof(task->task_data) - 1);
        }
    }
}

int main() {
    char data[150];
    Task task;

    printf("Enter task data: ");
    fgets(data, sizeof(data), stdin);

    reconstruct_task(&task, data);

    printf("Reconstructed Task: Task Name=%s, Task Data=%s\n", task.task_name, task.task_data);

    return 0;
}