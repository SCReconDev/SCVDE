#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* task_name;
    int priority;
} Task;

void load_task(const char* body, Task* task) {
    char* token = strtok((char*)body, "|");
    task->task_name = strdup(token);
    token = strtok(NULL, "|");
    task->priority = atoi(token);
}

void process_message(const char* body) {
    Task task;
    load_task(body, &task);
    printf("Task Name: %s, Priority: %d\n", task.task_name, task.priority);
    free(task.task_name);
}

int main() {
    const char* body = "send_email|1";
    process_message(body);
    return 0;
}