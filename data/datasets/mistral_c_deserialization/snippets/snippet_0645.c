#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* event_name;
    char* date;
    int attendees;
} Event;

void display_event(Event* event) {
    printf("Event Name: %s\n", event->event_name);
    printf("Date: %s\n", event->date);
    printf("Attendees: %d\n", event->attendees);
}

int main() {
    const char* json_str = "{\"event_name\":\"Tech Conference\",\"date\":\"2023-11-15\",\"attendees\":200}";
    struct json_object* parsed_json;
    struct json_object* event_name;
    struct json_object* date;
    struct json_object* attendees;
    Event event;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    json_object_object_get_ex(parsed_json, "event_name", &event_name);
    json_object_object_get_ex(parsed_json, "date", &date);
    json_object_object_get_ex(parsed_json, "attendees", &attendees);

    if (event_name == NULL || date == NULL || attendees == NULL) {
        fprintf(stderr, "Invalid JSON structure\n");
        json_object_put(parsed_json);
        return 1;
    }

    event.event_name = strdup(json_object_get_string(event_name));
    event.date = strdup(json_object_get_string(date));
    event.attendees = json_object_get_int(attendees);

    display_event(&event);

    free(event.event_name);
    free(event.date);
    json_object_put(parsed_json);

    return 0;
}