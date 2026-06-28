#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *job_id;
    char *task_data;
} Job;

void parse_job(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *job_id;
    struct json_object *task_data;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "job_id", &job_id)) {
        fprintf(stderr, "Job ID not found in JSON\n");
        json_object_put(parsed_json);
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "task_data", &task_data)) {
        fprintf(stderr, "Task data not found in JSON\n");
        json_object_put(parsed_json);
        return;
    }

    Job job;
    job.job_id = strdup(json_object_get_string(job_id));
    job.task_data = strdup(json_object_get_string(task_data));

    printf("Job ID: %s, Task Data: %s\n", job.job_id, job.task_data);

    free(job.job_id);
    free(job.task_data);
    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"job_id\":\"456\",\"task_data\":\"process_data\"}";
    parse_job(json_str);
    return 0;
}