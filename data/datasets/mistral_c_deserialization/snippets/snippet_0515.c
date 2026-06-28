#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char event[100];
    char date[20];
    char location[50];
} Event;

void display_event(Event *event) {
    printf("Event: %s\n", event->event);
    printf("Date: %s\n", event->date);
    printf("Location: %s\n", event->location);
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    FILE *file = fopen("event.json", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fread(buffer, sizeof(char), MAX_BUFFER_SIZE, file);
    fclose(file);

    struct json_object *parsed_json = json_tokener_parse(buffer);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    struct json_object *event_obj, *date_obj, *location_obj;
    if (!json_object_object_get_ex(parsed_json, "event", &event_obj) ||
        !json_object_object_get_ex(parsed_json, "date", &date_obj) ||
        !json_object_object_get_ex(parsed_json, "location", &location_obj)) {
        fprintf(stderr, "Error accessing JSON fields\n");
        json_object_put(parsed_json);
        return 1;
    }

    Event event;
    strncpy(event.event, json_object_get_string(event_obj), sizeof(event.event) - 1);
    strncpy(event.date, json_object_get_string(date_obj), sizeof(event.date) - 1);
    strncpy(event.location, json_object_get_string(location_obj), sizeof(event.location) - 1);

    display_event(&event);

    json_object_put(parsed_json);
    return 0;
}