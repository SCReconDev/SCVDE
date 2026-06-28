#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char task_name[50];
    char data[100];
} Task;

void process_task(const char* task_data) {
    Task* task = (Task*)malloc(sizeof(Task));
    memcpy(task, task_data, sizeof(Task));
    printf("Task: %s, Data: %s\n", task->task_name, task->data);
    free(task);
}

int main() {
    char task_data[200];
    printf("Enter task data: ");
    fgets(task_data, sizeof(task_data), stdin);
    process_task(task_data);
    return 0;
}