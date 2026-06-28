#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* task;
    int priority;
} Task;

void process_message(const char* body) {
    Task* task = (Task*)body;
    printf("Task: %s, Priority: %d\n", task->task, task->priority);
}

int main() {
    const char* message_body = "{\"task\":\"backup\",\"priority\":1}";
    process_message(message_body);
    return 0;
}