#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char task_name[50];
    char parameters[100];
} Task;

void load_task(const char* data, Task* task) {
    sscanf(data, "%49[^|]|%99[^|]", task->task_name, task->parameters);
}

int main() {
    char input_file[200];
    Task task;

    printf("Enter input file data (task_name|parameters): ");
    fgets(input_file, sizeof(input_file), stdin);
    input_file[strcspn(input_file, "\n")] = '\0';

    load_task(input_file, &task);

    printf("Task Name: %s\nParameters: %s\n", task.task_name, task.parameters);

    return 0;
}