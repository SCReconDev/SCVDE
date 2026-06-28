#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char task_id[50];
    char task_name[50];
    char task_data[200];
} Task;

bool validate_task(Task* task) {
    if (strlen(task->task_id) == 0 || strlen(task->task_name) == 0 || strlen(task->task_data) == 0) {
        return false;
    }
    return true;
}

void process_task(Task* task) {
    if (validate_task(task)) {
        printf("Task processed: %s, %s, %s\n", task->task_id, task->task_name, task->task_data);
    } else {
        printf("Invalid task data\n");
    }
}

int main() {
    Task task1 = {"task123", "example_task", "{\"param1\": \"value1\", \"param2\": \"value2\"}"};
    Task task2 = {"", "example_task", "{\"param1\": \"value1\", \"param2\": \"value2\"}"};

    process_task(&task1);
    process_task(&task2);

    return 0;
}