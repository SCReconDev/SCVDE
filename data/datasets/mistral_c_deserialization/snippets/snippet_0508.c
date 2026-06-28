#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* job_id;
    char* data;
} Job;

void process_job(const char* task_data) {
    cJSON* json = cJSON_Parse(task_data);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return;
    }

    cJSON* job_id = cJSON_GetObjectItemCaseSensitive(json, "job_id");
    cJSON* data = cJSON_GetObjectItemCaseSensitive(json, "data");

    if (cJSON_IsString(job_id) && (job_id->valuestring != NULL) && cJSON_IsString(data) && (data->valuestring != NULL)) {
        Job job;
        job.job_id = strdup(job_id->valuestring);
        job.data = strdup(data->valuestring);

        printf("Job ID: %s, Data: %s\n", job.job_id, job.data);

        free(job.job_id);
        free(job.data);
    }

    cJSON_Delete(json);
}

int main() {
    const char* task_data = "{\"job_id\":\"456\",\"data\":\"process\"}";
    process_job(task_data);
    return 0;
}