#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *job_name;
    int timeout;
} BackgroundJob;

void run_job(BackgroundJob *job) {
    printf("Running job: %s\n", job->job_name);
    printf("Timeout: %d\n", job->timeout);
}

int main() {
    const char *task_data = "{\"job_name\":\"data_backup\",\"timeout\":3600}";
    struct json_object *parsed_json;
    struct json_object *job_name;
    struct json_object *timeout;
    BackgroundJob job;

    parsed_json = json_tokener_parse(task_data);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    json_object_object_get_ex(parsed_json, "job_name", &job_name);
    json_object_object_get_ex(parsed_json, "timeout", &timeout);

    if (job_name == NULL || timeout == NULL) {
        fprintf(stderr, "Missing required fields in JSON\n");
        json_object_put(parsed_json);
        return 1;
    }

    job.job_name = strdup(json_object_get_string(job_name));
    job.timeout = json_object_get_int(timeout);

    run_job(&job);

    free(job.job_name);
    json_object_put(parsed_json);

    return 0;
}