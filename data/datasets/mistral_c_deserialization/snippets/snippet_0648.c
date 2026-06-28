#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* job_name;
    char* status;
    int progress;
} Job;

void display_job(Job* job) {
    printf("Job Name: %s\n", job->job_name);
    printf("Status: %s\n", job->status);
    printf("Progress: %d%%\n", job->progress);
}

int main() {
    const char* json_str = "{\"job_name\":\"Data Processing\",\"status\":\"Running\",\"progress\":75}";
    struct json_object* parsed_json;
    struct json_object* job_name;
    struct json_object* status;
    struct json_object* progress;
    Job job;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    json_object_object_get_ex(parsed_json, "job_name", &job_name);
    json_object_object_get_ex(parsed_json, "status", &status);
    json_object_object_get_ex(parsed_json, "progress", &progress);

    if (job_name == NULL || status == NULL || progress == NULL) {
        fprintf(stderr, "Invalid JSON structure\n");
        json_object_put(parsed_json);
        return 1;
    }

    job.job_name = strdup(json_object_get_string(job_name));
    job.status = strdup(json_object_get_string(status));
    job.progress = json_object_get_int(progress);

    display_job(&job);

    free(job.job_name);
    free(job.status);
    json_object_put(parsed_json);

    return 0;
}