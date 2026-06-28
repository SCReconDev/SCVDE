#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char task_id[50];
    char task_data[200];
} TaskData;

void deserialize_task_data(TaskData *task_data, const char *data) {
    memcpy(task_data, data, sizeof(TaskData));
}

void process_task(const char *serialized_task) {
    TaskData task_data;
    deserialize_task_data(&task_data, serialized_task);
    printf("Processing task: %s\n", task_data.task_id);
}

int main() {
    char serialized_task[250];
    printf("Enter serialized task: ");
    fgets(serialized_task, sizeof(serialized_task), stdin);
    serialized_task[strcspn(serialized_task, "\n")] = '\0';

    process_task(serialized_task);
    return 0;
}