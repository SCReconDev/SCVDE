#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <json-c/json.h>

typedef struct {
    char *log_id;
    char *log_message;
    char *log_timestamp;
} Log;

bool validate_log_schema(const json_object *jobj) {
    json_object_object_foreach(jobj, key, val) {
        if (strcmp(key, "log_id") == 0 && json_object_get_type(val) != json_type_string) {
            return false;
        }
        if (strcmp(key, "log_message") == 0 && json_object_get_type(val) != json_type_string) {
            return false;
        }
        if (strcmp(key, "log_timestamp") == 0 && json_object_get_type(val) != json_type_string) {
            return false;
        }
    }
    return true;
}

Log *deserialize_log(const char *json_str) {
    json_object *jobj = json_tokener_parse(json_str);
    if (!jobj) {
        return NULL;
    }

    if (!validate_log_schema(jobj)) {
        json_object_put(jobj);
        return NULL;
    }

    Log *log = malloc(sizeof(Log));
    if (!log) {
        json_object_put(jobj);
        return NULL;
    }

    json_object *log_id_obj, *log_message_obj, *log_timestamp_obj;
    if (json_object_object_get_ex(jobj, "log_id", &log_id_obj)) {
        log->log_id = strdup(json_object_get_string(log_id_obj));
    } else {
        log->log_id = NULL;
    }

    if (json_object_object_get_ex(jobj, "log_message", &log_message_obj)) {
        log->log_message = strdup(json_object_get_string(log_message_obj));
    } else {
        log->log_message = NULL;
    }

    if (json_object_object_get_ex(jobj, "log_timestamp", &log_timestamp_obj)) {
        log->log_timestamp = strdup(json_object_get_string(log_timestamp_obj));
    } else {
        log->log_timestamp = NULL;
    }

    json_object_put(jobj);
    return log;
}

void free_log(Log *log) {
    if (log) {
        free(log->log_id);
        free(log->log_message);
        free(log->log_timestamp);
        free(log);
    }
}

int main() {
    const char *json_str = "{\"log_id\":\"13579\",\"log_message\":\"System started\",\"log_timestamp\":\"2023-12-15T10:00:00\"}";
    Log *log = deserialize_log(json_str);

    if (log) {
        printf("Log ID: %s\n", log->log_id);
        printf("Log Message: %s\n", log->log_message);
        printf("Log Timestamp: %s\n", log->log_timestamp);
        free_log(log);
    } else {
        printf("Failed to deserialize log.\n");
    }

    return 0;
}