#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char task_id[37];
    char task_data[255];
} Task;

bool validate_task(Task* task) {
    if (strlen(task->task_id) != 36) {
        return false;
    }
    if (strlen(task->task_data) >= 255) {
        return false;
    }
    return true;
}

void process_task(Task* task) {
    if (validate_task(task)) {
        printf("Task ID: %s, Data: %s\n", task->task_id, task->task_data);
    } else {
        printf("Invalid task data\n");
    }
}

int main() {
    Task task1 = {"123e4567-e89b-12d3-a456-426614174000", "{\"action\": \"process\", \"data\": \"sample\"}"};
    Task task2 = {"invalid-task-id", "{\"invalid\": \"data\"}"};

    process_task(&task1);
    process_task(&task2);

    return 0;
}