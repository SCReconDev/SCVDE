#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *event_name;
    char *date;
    int attendees;
} Event;

void deserialize_event(const char *json_str, Event *event) {
    struct json_object *parsed_json;
    struct json_object *name_obj;
    struct json_object *date_obj;
    struct json_object *attendees_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (json_object_object_get_ex(parsed_json, "event_name", &name_obj)) {
        event->event_name = strdup(json_object_get_string(name_obj));
    }

    if (json_object_object_get_ex(parsed_json, "date", &date_obj)) {
        event->date = strdup(json_object_get_string(date_obj));
    }

    if (json_object_object_get_ex(parsed_json, "attendees", &attendees_obj)) {
        event->attendees = json_object_get_int(attendees_obj);
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"event_name\":\"Conference\",\"date\":\"2023-12-25\",\"attendees\":100}";
    Event event;

    deserialize_event(json_str, &event);

    printf("Event Name: %s\n", event.event_name);
    printf("Date: %s\n", event.date);
    printf("Attendees: %d\n", event.attendees);

    free(event.event_name);
    free(event.date);
    return 0;
}