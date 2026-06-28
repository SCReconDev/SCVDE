#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char task_name[50];
    int priority;
} Task;

void deserialize_task(const char* data, Task* task) {
    char* decoded_data = malloc(strlen(data) + 1);
    strcpy(decoded_data, data);
    sscanf(decoded_data, "%49s %d", task->task_name, &task->priority);
    free(decoded_data);
}

void process_background_job(const char* task_data) {
    Task task;
    deserialize_task(task_data, &task);
    printf("Task: %s, Priority: %d\n", task.task_name, task.priority);
}

int main() {
    const char* task_data = "data_processing 5";
    process_background_job(task_data);
    return 0;
}