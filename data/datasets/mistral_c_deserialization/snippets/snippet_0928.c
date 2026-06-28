#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *job_name;
    int job_id;
    char *status;
} Job;

void monitor_job(Job *job) {
    printf("Job: %s, ID: %d, Status: %s\n", job->job_name, job->job_id, job->status);
}

int main() {
    const char *json_str = "{\"job_name\":\"Data Processing\", \"job_id\":501, \"status\":\"Running\"}";
    struct json_object *parsed_json;
    struct json_object *job_name_obj, *job_id_obj, *status_obj;
    Job job;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    if (!json_object_object_get_ex(parsed_json, "job_name", &job_name_obj) ||
        !json_object_object_get_ex(parsed_json, "job_id", &job_id_obj) ||
        !json_object_object_get_ex(parsed_json, "status", &status_obj)) {
        fprintf(stderr, "Error extracting JSON fields\n");
        json_object_put(parsed_json);
        return 1;
    }

    job.job_name = strdup(json_object_get_string(job_name_obj));
    job.job_id = json_object_get_int(job_id_obj);
    job.status = strdup(json_object_get_string(status_obj));

    monitor_job(&job);

    free(job.job_name);
    free(job.status);
    json_object_put(parsed_json);

    return 0;
}