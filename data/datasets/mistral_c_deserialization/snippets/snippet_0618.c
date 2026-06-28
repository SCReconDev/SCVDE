#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char job_id[50];
    char job_type[50];
    char job_data[200];
} Job;

int validate_job_json(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *job_id_obj, *job_type_obj, *job_data_obj;

    parsed_json = json_tokener_parse(json_str);
    if (!parsed_json) {
        return 0;
    }

    if (!json_object_object_get_ex(parsed_json, "job_id", &job_id_obj) ||
        !json_object_object_get_ex(parsed_json, "job_type", &job_type_obj) ||
        !json_object_object_get_ex(parsed_json, "job_data", &job_data_obj)) {
        json_object_put(parsed_json);
        return 0;
    }

    if (json_object_get_type(job_id_obj) != json_type_string ||
        json_object_get_type(job_type_obj) != json_type_string ||
        json_object_get_type(job_data_obj) != json_type_string) {
        json_object_put(parsed_json);
        return 0;
    }

    json_object_put(parsed_json);
    return 1;
}

Job* deserialize_job(const char *json_str) {
    Job *job = malloc(sizeof(Job));
    if (!job) {
        return NULL;
    }

    struct json_object *parsed_json;
    struct json_object *job_id_obj, *job_type_obj, *job_data_obj;

    parsed_json = json_tokener_parse(json_str);
    if (!parsed_json) {
        free(job);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "job_id", &job_id_obj);
    json_object_object_get_ex(parsed_json, "job_type", &job_type_obj);
    json_object_object_get_ex(parsed_json, "job_data", &job_data_obj);

    strncpy(job->job_id, json_object_get_string(job_id_obj), sizeof(job->job_id) - 1);
    strncpy(job->job_type, json_object_get_string(job_type_obj), sizeof(job->job_type) - 1);
    strncpy(job->job_data, json_object_get_string(job_data_obj), sizeof(job->job_data) - 1);

    json_object_put(parsed_json);
    return job;
}

void process_job_data(const char *json_str) {
    if (!validate_job_json(json_str)) {
        printf("Invalid job data format\n");
        return;
    }

    Job *job = deserialize_job(json_str);
    if (!job) {
        printf("Failed to deserialize job data\n");
        return;
    }

    printf("Job ID: %s, Job Type: %s, Job Data: %s\n", job->job_id, job->job_type, job->job_data);
    free(job);
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    printf("Enter job data in JSON format:\n");
    fgets(buffer, sizeof(buffer), stdin);

    process_job_data(buffer);

    return 0;
}