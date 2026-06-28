#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* task_name;
    int duration;
} Job;

void process_job(const char* data) {
    Job* job = (Job*)malloc(sizeof(Job));
    memcpy(job, data, sizeof(Job));

    printf("Job: %s, Duration: %d\n", job->task_name, job->duration);
    free(job);
}

int main() {
    char* task_data = "data_processing\045";
    process_job(task_data);
    return 0;
}