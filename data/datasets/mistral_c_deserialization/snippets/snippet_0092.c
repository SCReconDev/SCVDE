#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char task[50];
    int id;
} BackgroundTask;

void load_task(BackgroundTask *task, const char *data) {
    char *token = strtok((char *)data, "-");
    strcpy(task->task, token);
    token = strtok(NULL, "-");
    task->id = atoi(token);
}

int main() {
    char data[100];
    BackgroundTask task;

    printf("Enter task data: ");
    fgets(data, sizeof(data), stdin);

    load_task(&task, data);

    printf("Background Task: Task=%s, ID=%d\n", task.task, task.id);

    return 0;
}