#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *event_name;
    char *event_date;
    int attendees;
} Event;

void deserialize_event(const char *json_str, Event *event) {
    struct json_object *parsed_json;
    struct json_object *event_name;
    struct json_object *event_date;
    struct json_object *attendees;

    parsed_json = json_tokener_parse(json_str);
    if (json_object_object_get_ex(parsed_json, "event_name", &event_name)) {
        event->event_name = strdup(json_object_get_string(event_name));
    }
    if (json_object_object_get_ex(parsed_json, "event_date", &event_date)) {
        event->event_date = strdup(json_object_get_string(event_date));
    }
    if (json_object_object_get_ex(parsed_json, "attendees", &attendees)) {
        event->attendees = json_object_get_int(attendees);
    }
    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"event_name\":\"Sample Event\",\"event_date\":\"2023-12-31\",\"attendees\":50}";
    Event event;

    deserialize_event(json_str, &event);

    printf("Event Name: %s\n", event.event_name);
    printf("Event Date: %s\n", event.event_date);
    printf("Attendees: %d\n", event.attendees);

    free(event.event_name);
    free(event.event_date);
    return 0;
}