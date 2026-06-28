#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *job_id;
    char *job_name;
    int progress;
} Job;

void parse_job_data(const char *json_str, Job *job) {
    struct json_object *parsed_json;
    struct json_object *id_obj;
    struct json_object *name_obj;
    struct json_object *progress_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (json_object_object_get_ex(parsed_json, "job_id", &id_obj)) {
        job->job_id = strdup(json_object_get_string(id_obj));
    }

    if (json_object_object_get_ex(parsed_json, "job_name", &name_obj)) {
        job->job_name = strdup(json_object_get_string(name_obj));
    }

    if (json_object_object_get_ex(parsed_json, "progress", &progress_obj)) {
        job->progress = json_object_get_int(progress_obj);
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"job_id\":\"J456\",\"job_name\":\"Data Processing\",\"progress\":75}";
    Job job;

    parse_job_data(json_str, &job);

    printf("Job ID: %s\n", job.job_id);
    printf("Job Name: %s\n", job.job_name);
    printf("Progress: %d%%\n", job.progress);

    free(job.job_id);
    free(job.job_name);
    return 0;
}