#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char task_name[50];
    char data[100];
} Task;

void load_task(const char* data, Task* task) {
    sscanf(data, "%49s %99[^\n]", task->task_name, task->data);
}

int main() {
    char input_file[200];
    Task task;

    printf("Enter input file data (task_name data): ");
    fgets(input_file, sizeof(input_file), stdin);

    load_task(input_file, &task);

    printf("Loaded Task: Task Name=%s, Data=%s\n", task.task_name, task.data);

    return 0;
}