#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* task;
    int priority;
} Task;

void load_task(Task* task, const char* body) {
    char* token = strtok((char*)body, ";");
    task->task = strdup(token);
    token = strtok(NULL, ";");
    task->priority = atoi(token);
}

void process_message(const char* body) {
    Task task;
    load_task(&task, body);
    printf("Task: %s, Priority: %d\n", task.task, task.priority);
    free(task.task);
}

int main() {
    const char* body = "Complete project;1";
    process_message(body);
    return 0;
}