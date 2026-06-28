#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char task_name[50];
    char task_data[100];
} TaskData;

void deserialize_task(const char* data, TaskData* task) {
    sscanf(data, "%49s %99[^\n]", task->task_name, task->task_data);
}

void process_task(const char* data) {
    TaskData task;
    deserialize_task(data, &task);
    printf("Task: %s, Data: %s\n", task.task_name, task.task_data);
}

int main() {
    char data[200];
    printf("Enter task data: ");
    fgets(data, sizeof(data), stdin);
    process_task(data);
    return 0;
}