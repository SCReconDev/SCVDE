#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* command;
    int priority;
} Task;

void restore_command(const char* input) {
    Task* task = (Task*)malloc(sizeof(Task));
    memcpy(task, input, sizeof(Task));

    printf("Command: %s, Priority: %d\n", task->command, task->priority);
    free(task);
}

int main() {
    char* input_file = "backup\01";
    restore_command(input_file);
    return 0;
}