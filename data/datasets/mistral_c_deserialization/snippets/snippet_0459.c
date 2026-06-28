#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char task_name[50];
    int priority;
} Task;

void deserialize_task(char* data, Task* task) {
    char* token = strtok(data, ",");
    strcpy(task->task_name, token);
    token = strtok(NULL, ",");
    task->priority = atoi(token);
}

void execute_task(char* input_file) {
    Task task;
    deserialize_task(input_file, &task);
    printf("Executing task: %s, priority %d\n", task.task_name, task.priority);
}

int main() {
    char input_file[] = "backup,1";
    execute_task(input_file);
    return 0;
}