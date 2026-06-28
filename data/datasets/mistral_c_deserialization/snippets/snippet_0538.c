#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* job_id;
    char* job_data;
} Job;

void deserialize_job(const char* json_str, Job* job) {
    struct json_object* parsed_json;
    struct json_object* job_id;
    struct json_object* job_data;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "job_id", &job_id);
    json_object_object_get_ex(parsed_json, "job_data", &job_data);

    if (job_id != NULL && job_data != NULL) {
        job->job_id = strdup(json_object_get_string(job_id));
        job->job_data = strdup(json_object_get_string(job_data));
    } else {
        fprintf(stderr, "Invalid JSON format\n");
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"job_id\":\"job123\",\"job_data\":\"process_data\"}";
    Job job;

    deserialize_job(json_str, &job);

    printf("Job ID: %s\n", job.job_id);
    printf("Job Data: %s\n", job.job_data);

    free(job.job_id);
    free(job.job_data);

    return 0;
}