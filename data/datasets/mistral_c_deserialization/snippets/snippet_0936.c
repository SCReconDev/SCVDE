#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* event_name;
    char* event_date;
    char* location;
} Event;

void deserialize_event(const char* json_str, Event* event) {
    struct json_object* parsed_json;
    struct json_object* event_name;
    struct json_object* event_date;
    struct json_object* location;

    parsed_json = json_tokener_parse(json_str);

    if (json_object_object_get_ex(parsed_json, "event_name", &event_name)) {
        event->event_name = strdup(json_object_get_string(event_name));
    }

    if (json_object_object_get_ex(parsed_json, "event_date", &event_date)) {
        event->event_date = strdup(json_object_get_string(event_date));
    }

    if (json_object_object_get_ex(parsed_json, "location", &location)) {
        event->location = strdup(json_object_get_string(location));
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"event_name\":\"Tech Conference\",\"event_date\":\"2023-11-15\",\"location\":\"San Francisco\"}";
    Event event;

    deserialize_event(json_str, &event);

    printf("Event Name: %s\n", event.event_name);
    printf("Event Date: %s\n", event.event_date);
    printf("Location: %s\n", event.location);

    free(event.event_name);
    free(event.event_date);
    free(event.location);

    return 0;
}