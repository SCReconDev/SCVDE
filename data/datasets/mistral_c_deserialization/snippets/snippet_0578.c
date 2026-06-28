#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <json-c/json.h>

typedef struct {
    char *report_id;
    char *report_title;
    char *report_content;
} Report;

bool validate_report_schema(const json_object *jobj) {
    json_object_object_foreach(jobj, key, val) {
        if (strcmp(key, "report_id") == 0 && json_object_get_type(val) != json_type_string) {
            return false;
        }
        if (strcmp(key, "report_title") == 0 && json_object_get_type(val) != json_type_string) {
            return false;
        }
        if (strcmp(key, "report_content") == 0 && json_object_get_type(val) != json_type_string) {
            return false;
        }
    }
    return true;
}

Report *deserialize_report(const char *json_str) {
    json_object *jobj = json_tokener_parse(json_str);
    if (!jobj) {
        return NULL;
    }

    if (!validate_report_schema(jobj)) {
        json_object_put(jobj);
        return NULL;
    }

    Report *report = malloc(sizeof(Report));
    if (!report) {
        json_object_put(jobj);
        return NULL;
    }

    json_object *report_id_obj, *report_title_obj, *report_content_obj;
    if (json_object_object_get_ex(jobj, "report_id", &report_id_obj)) {
        report->report_id = strdup(json_object_get_string(report_id_obj));
    } else {
        report->report_id = NULL;
    }

    if (json_object_object_get_ex(jobj, "report_title", &report_title_obj)) {
        report->report_title = strdup(json_object_get_string(report_title_obj));
    } else {
        report->report_title = NULL;
    }

    if (json_object_object_get_ex(jobj, "report_content", &report_content_obj)) {
        report->report_content = strdup(json_object_get_string(report_content_obj));
    } else {
        report->report_content = NULL;
    }

    json_object_put(jobj);
    return report;
}

void free_report(Report *report) {
    if (report) {
        free(report->report_id);
        free(report->report_title);
        free(report->report_content);
        free(report);
    }
}

int main() {
    const char *json_str = "{\"report_id\":\"24680\",\"report_title\":\"Annual Report\",\"report_content\":\"This is the annual report content.\"}";
    Report *report = deserialize_report(json_str);

    if (report) {
        printf("Report ID: %s\n", report->report_id);
        printf("Report Title: %s\n", report->report_title);
        printf("Report Content: %s\n", report->report_content);
        free_report(report);
    } else {
        printf("Failed to deserialize report.\n");
    }

    return 0;
}