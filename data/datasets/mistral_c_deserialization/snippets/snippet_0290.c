#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char task[50];
    char data[100];
} Task;

void process_task(Task *task, const char *data) {
    sscanf(data, "%49s %99[^\n]", task->task, task->data);
}

void handle_background_task(const char *data) {
    Task task;
    process_task(&task, data);
    printf("Background Task: %s with data %s\n", task.task, task.data);
}

int main() {
    char data[200];
    printf("Enter task data: ");
    fgets(data, sizeof(data), stdin);
    handle_background_task(data);
    return 0;
}