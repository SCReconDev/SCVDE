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
    struct json_object *name_obj, *date_obj, *attendees_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "event_name", &name_obj);
    json_object_object_get_ex(parsed_json, "date", &date_obj);
    json_object_object_get_ex(parsed_json, "attendees", &attendees_obj);

    if (name_obj != NULL && json_object_get_type(name_obj) == json_type_string) {
        event->event_name = strdup(json_object_get_string(name_obj));
    }

    if (date_obj != NULL && json_object_get_type(date_obj) == json_type_string) {
        event->date = strdup(json_object_get_string(date_obj));
    }

    if (attendees_obj != NULL && json_object_get_type(attendees_obj) == json_type_int) {
        event->attendees = json_object_get_int(attendees_obj);
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"event_name\":\"Tech Conference\",\"date\":\"2023-10-15\",\"attendees\":200}";
    Event event;

    deserialize_event(json_str, &event);

    printf("Event Name: %s\n", event.event_name);
    printf("Date: %s\n", event.date);
    printf("Attendees: %d\n", event.attendees);

    free(event.event_name);
    free(event.date);
    return 0;
}