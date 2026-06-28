#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* task_id;
    char* data;
} Task;

Task* load_task(const char* file) {
    FILE* fp = fopen(file, "r");
    char buffer[1024];
    fgets(buffer, sizeof(buffer), fp);
    fclose(fp);

    Task* task = malloc(sizeof(Task));
    char* token = strtok(buffer, ",");
    task->task_id = strdup(token);
    token = strtok(NULL, ",");
    task->data = strdup(token);
    return task;
}

void process_task(const char* file) {
    Task* task = load_task(file);
    printf("Task ID: %s\n", task->task_id);
    free(task->task_id);
    free(task->data);
    free(task);
}

int main() {
    process_task("task.txt");
    return 0;
}