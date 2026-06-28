#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* task_name;
    char* task_data;
} TaskData;

void process_job(const char* serialized_data) {
    TaskData* task = (TaskData*)serialized_data;
    printf("Task Name: %s, Task Data: %s\n", task->task_name, task->task_data);
}

int main() {
    const char* serialized_data = "{\"task_name\":\"data_processing\",\"task_data\":\"large_dataset\"}";
    process_job(serialized_data);
    return 0;
}