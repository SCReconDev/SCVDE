#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char job_id[50];
    char task_data[100];
} Job;

void reconstruct_job(const char* data, Job* job) {
    sscanf(data, "%49s %99[^\n]", job->job_id, job->task_data);
}

int main() {
    char serialized_data[200];
    Job job;

    printf("Enter serialized job data (job_id task_data): ");
    fgets(serialized_data, sizeof(serialized_data), stdin);

    reconstruct_job(serialized_data, &job);

    printf("Reconstructed Job: Job ID=%s, Task Data=%s\n", job.job_id, job.task_data);

    return 0;
}