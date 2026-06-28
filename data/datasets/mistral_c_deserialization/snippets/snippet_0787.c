#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *report_id;
    char *report_content;
} Report;

void deserialize_report(const char *json_str, Report *report) {
    struct json_object *parsed_json;
    struct json_object *report_id_obj, *report_content_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "report_id", &report_id_obj) ||
        !json_object_object_get_ex(parsed_json, "report_content", &report_content_obj)) {
        fprintf(stderr, "Error: Missing required fields\n");
        json_object_put(parsed_json);
        return;
    }

    if (json_object_get_type(report_id_obj) != json_type_string ||
        json_object_get_type(report_content_obj) != json_type_string) {
        fprintf(stderr, "Error: Invalid field types\n");
        json_object_put(parsed_json);
        return;
    }

    report->report_id = strdup(json_object_get_string(report_id_obj));
    report->report_content = strdup(json_object_get_string(report_content_obj));

    json_object_put(parsed_json);
}

void process_report(Report *report) {
    printf("Report ID: %s\n", report->report_id);
    printf("Report Content: %s\n", report->report_content);
}

int main() {
    const char *json_str = "{\"report_id\": \"54321\", \"report_content\": \"This is a sample report content.\"}";
    Report report;

    deserialize_report(json_str, &report);
    process_report(&report);

    free(report.report_id);
    free(report.report_content);
    return 0;
}