#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char task_name[50];
    int priority;
} Task;

void process_message(char* body) {
    Task* task = (Task*)malloc(sizeof(Task));
    memcpy(task, body, sizeof(Task));
    printf("Task processed: %s (Priority: %d)\n", task->task_name, task->priority);
    free(task);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <incoming_body>\n", argv[0]);
        return 1;
    }

    char* body = argv[1];
    process_message(body);

    return 0;
}