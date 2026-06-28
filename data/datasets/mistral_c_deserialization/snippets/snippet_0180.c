#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* task;
    int id;
} Task;

void process_task(char* data) {
    Task* task = (Task*)malloc(sizeof(Task));
    memcpy(task, data, sizeof(Task));
    printf("Task ID: %d\n", task->id);
    free(task);
}

int main() {
    char data[1024];
    fgets(data, sizeof(data), stdin);
    process_task(data);
    return 0;
}