#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* task;
    int priority;
} Job;

void reconstruct_job(Job* job, const char* data) {
    char* token = strtok((char*)data, "-");
    job->task = strdup(token);
    token = strtok(NULL, "-");
    job->priority = atoi(token);
}

void process_job(const char* data) {
    Job job;
    reconstruct_job(&job, data);
    printf("Task: %s, Priority: %d\n", job.task, job.priority);
    free(job.task);
}

int main() {
    const char* data = "Backup database-2";
    process_job(data);
    return 0;
}