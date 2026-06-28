#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* job_id;
    char* task_data;
} BackgroundJob;

void process_background_job(BackgroundJob* job) {
    printf("Job ID: %s, Task Data: %s\n", job->job_id, job->task_data);
}

int main() {
    const char* serialized_task_data = "{\"job_id\":\"job456\",\"task_data\":\"{\\\"type\\\":\\\"cleanup\\\",\\\"params\\\":{\\\"path\\\":\\\"/tmp\\\"}}\"}";
    struct json_object* parsed_json;
    struct json_object* job_id_obj;
    struct json_object* task_data_obj;
    BackgroundJob job;

    parsed_json = json_tokener_parse(serialized_task_data);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    if (!json_object_object_get_ex(parsed_json, "job_id", &job_id_obj) ||
        !json_object_object_get_ex(parsed_json, "task_data", &task_data_obj)) {
        fprintf(stderr, "Error extracting JSON fields\n");
        json_object_put(parsed_json);
        return 1;
    }

    job.job_id = strdup(json_object_get_string(job_id_obj));
    job.task_data = strdup(json_object_get_string(task_data_obj));

    process_background_job(&job);

    free(job.job_id);
    free(job.task_data);
    json_object_put(parsed_json);

    return 0;
}