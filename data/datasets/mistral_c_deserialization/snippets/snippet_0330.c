#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char job_id[50];
    char task_data[100];
} Job;

void reconstruct_job(const char* data, Job* job) {
    sscanf(data, "%49[^|]|%99[^|]", job->job_id, job->task_data);
}

int main() {
    char serialized_data[200];
    Job job;

    printf("Enter serialized task data (job_id|task_data): ");
    fgets(serialized_data, sizeof(serialized_data), stdin);
    serialized_data[strcspn(serialized_data, "\n")] = '\0';

    reconstruct_job(serialized_data, &job);

    printf("Job ID: %s\nTask Data: %s\n", job.job_id, job.task_data);

    return 0;
}