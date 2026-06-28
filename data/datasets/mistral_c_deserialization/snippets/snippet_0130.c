#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TASK_SIZE 1024

void process_task(const char *task_data) {
    char *decoded_task = (char *)malloc(TASK_SIZE);
    if (decoded_task == NULL) {
        return;
    }

    size_t decoded_length = TASK_SIZE;
    if (base64_decode(task_data, decoded_task, &decoded_length) != 0) {
        free(decoded_task);
        return;
    }

    void *task = deserialize_task(decoded_task, decoded_length);
    if (task == NULL) {
        free(decoded_task);
        return;
    }

    printf("Task processed successfully.\n");

    free(task);
    free(decoded_task);
}

int main() {
    char task_data[TASK_SIZE];
    printf("Enter task data: ");
    fgets(task_data, TASK_SIZE, stdin);
    task_data[strcspn(task_data, "\n")] = '\0';

    process_task(task_data);

    return 0;
}