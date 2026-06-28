#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *event_name;
    char *date;
    int attendees;
} Event;

void schedule_event(Event *event) {
    printf("Event: %s, Date: %s, Attendees: %d\n", event->event_name, event->date, event->attendees);
}

int main() {
    const char *json_str = "{\"event_name\":\"Tech Conference\", \"date\":\"2023-11-15\", \"attendees\":200}";
    struct json_object *parsed_json;
    struct json_object *event_name_obj, *date_obj, *attendees_obj;
    Event event;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    if (!json_object_object_get_ex(parsed_json, "event_name", &event_name_obj) ||
        !json_object_object_get_ex(parsed_json, "date", &date_obj) ||
        !json_object_object_get_ex(parsed_json, "attendees", &attendees_obj)) {
        fprintf(stderr, "Error extracting JSON fields\n");
        json_object_put(parsed_json);
        return 1;
    }

    event.event_name = strdup(json_object_get_string(event_name_obj));
    event.date = strdup(json_object_get_string(date_obj));
    event.attendees = json_object_get_int(attendees_obj);

    schedule_event(&event);

    free(event.event_name);
    free(event.date);
    json_object_put(parsed_json);

    return 0;
}