#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *event_name;
    char *event_date;
} Event;

void deserialize_event(const char *json_str, Event *event) {
    struct json_object *parsed_json;
    struct json_object *event_name_obj, *event_date_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "event_name", &event_name_obj) ||
        !json_object_object_get_ex(parsed_json, "event_date", &event_date_obj)) {
        fprintf(stderr, "Error: Missing required fields\n");
        json_object_put(parsed_json);
        return;
    }

    if (json_object_get_type(event_name_obj) != json_type_string ||
        json_object_get_type(event_date_obj) != json_type_string) {
        fprintf(stderr, "Error: Invalid field types\n");
        json_object_put(parsed_json);
        return;
    }

    event->event_name = strdup(json_object_get_string(event_name_obj));
    event->event_date = strdup(json_object_get_string(event_date_obj));

    json_object_put(parsed_json);
}

void process_event(Event *event) {
    printf("Event Name: %s\n", event->event_name);
    printf("Event Date: %s\n", event->event_date);
}

int main() {
    const char *json_str = "{\"event_name\": \"Tech Conference\", \"event_date\": \"2023-11-15\"}";
    Event event;

    deserialize_event(json_str, &event);
    process_event(&event);

    free(event.event_name);
    free(event.event_date);
    return 0;
}