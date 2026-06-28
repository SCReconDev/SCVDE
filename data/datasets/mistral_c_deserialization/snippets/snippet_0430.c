#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char task_name[50];
    char task_data[100];
} Task;

void deserialize_task(Task *task, const char *data) {
    char *token = strtok((char *)data, "|");
    strcpy(task->task_name, token);
    token = strtok(NULL, "|");
    strcpy(task->task_data, token);
}

void process_task(const char *task_data) {
    Task task;
    deserialize_task(&task, task_data);
    printf("Task processed: Name=%s, Data=%s\n", task.task_name, task.task_data);
}

int main() {
    const char *task_data = "example_task|Task data";
    process_task(task_data);
    return 0;
}