#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* job_id;
    char* task_data;
} Job;

Job* reconstruct_job(const char* data) {
    Job* job = malloc(sizeof(Job));
    char* token = strtok((char*)data, "|");
    job->job_id = strdup(token);
    token = strtok(NULL, "|");
    job->task_data = strdup(token);
    return job;
}

void run_job(const char* data) {
    Job* job = reconstruct_job(data);
    printf("Job ID: %s\n", job->job_id);
    free(job->job_id);
    free(job->task_data);
    free(job);
}

int main() {
    char* data = "456|process=start";
    run_job(data);
    return 0;
}