#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *meeting_id;
    char *meeting_time;
} Meeting;

void deserialize_meeting(const char *json_str, Meeting *meeting) {
    struct json_object *parsed_json;
    struct json_object *meeting_id_obj, *meeting_time_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "meeting_id", &meeting_id_obj) ||
        !json_object_object_get_ex(parsed_json, "meeting_time", &meeting_time_obj)) {
        fprintf(stderr, "Error: Missing required fields\n");
        json_object_put(parsed_json);
        return;
    }

    if (json_object_get_type(meeting_id_obj) != json_type_string ||
        json_object_get_type(meeting_time_obj) != json_type_string) {
        fprintf(stderr, "Error: Invalid field types\n");
        json_object_put(parsed_json);
        return;
    }

    meeting->meeting_id = strdup(json_object_get_string(meeting_id_obj));
    meeting->meeting_time = strdup(json_object_get_string(meeting_time_obj));

    json_object_put(parsed_json);
}

void process_meeting(Meeting *meeting) {
    printf("Meeting ID: %s\n", meeting->meeting_id);
    printf("Meeting Time: %s\n", meeting->meeting_time);
}

int main() {
    const char *json_str = "{\"meeting_id\": \"13579\", \"meeting_time\": \"2023-11-20T14:30:00\"}";
    Meeting meeting;

    deserialize_meeting(json_str, &meeting);
    process_meeting(&meeting);

    free(meeting.meeting_id);
    free(meeting.meeting_time);
    return 0;
}