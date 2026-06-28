#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* task_name;
    char* task_data;
} Task;

void execute_task(Task* task) {
    printf("Task Name: %s\n", task->task_name);
    printf("Task Data: %s\n", task->task_data);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <serialized_task_data>\n", argv[0]);
        return 1;
    }

    char* serialized_task_data = argv[1];
    Task* task = (Task*)serialized_task_data;
    execute_task(task);

    return 0;
}