#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* task_name;
    char* parameters;
} Task;

void deserialize_task(char* data, Task* task) {
    char* token = strtok(data, ":");
    task->task_name = strdup(token);
    token = strtok(NULL, ":");
    task->parameters = strdup(token);
}

void process_task(char* serialized_data) {
    Task task;
    deserialize_task(serialized_data, &task);
    printf("Task Name: %s, Parameters: %s\n", task.task_name, task.parameters);
    free(task.task_name);
    free(task.parameters);
}

int main() {
    char* serialized_data = "backup_data:{\"source\":\"C:\",\"destination\":\"D:\"}";
    process_task(serialized_data);
    return 0;
}