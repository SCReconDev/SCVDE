#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* message;
    int priority;
} Task;

void load_task(Task* task, const char* data) {
    char* token = strtok((char*)data, "|");
    task->message = strdup(token);
    token = strtok(NULL, "|");
    task->priority = atoi(token);
}

int main() {
    char* data = "Complete the project|1";
    Task task;
    load_task(&task, data);
    printf("Task: %s, Priority: %d\n", task.message, task.priority);
    free(task.message);
    return 0;
}