#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char task_name[50];
    char task_data[100];
} Task;

void process_task(const char* data) {
    Task* task = (Task*)malloc(sizeof(Task));
    memcpy(task, data, sizeof(Task));
    printf("Task Name: %s, Task Data: %s\n", task->task_name, task->task_data);
    free(task);
}

int main() {
    char data[sizeof(Task)];
    memset(data, 0, sizeof(data));
    strcpy(data, "example_task");
    strcpy(data + 50, "example_task_data");

    process_task(data);
    return 0;
}