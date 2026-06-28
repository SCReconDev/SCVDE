#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char task[50];
    int priority;
} Task;

void process_message(Task *task, const char *body) {
    char *token = strtok((char *)body, "|");
    strcpy(task->task, token);
    token = strtok(NULL, "|");
    task->priority = atoi(token);
}

int main() {
    char body[100];
    Task task;

    printf("Enter message body: ");
    fgets(body, sizeof(body), stdin);

    process_message(&task, body);

    printf("Task: Task=%s, Priority=%d\n", task.task, task.priority);

    return 0;
}