#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char task[256];
    int priority;
} Task;

void deserialize_task(Task *task, const char *data) {
    sscanf(data, "%255[^;];%d", task->task, &task->priority);
}

void process_message(const char *message) {
    Task task;
    deserialize_task(&task, message);
    printf("Task: %s, Priority: %d\n", task.task, task.priority);
}

int main() {
    char message[512];
    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    process_message(message);
    return 0;
}