#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char event[50];
    char date[50];
    char location[50];
} Event;

int validate_event_schema(json_object *jobj) {
    json_object_object_foreach(jobj, key, val) {
        if (strcmp(key, "event") == 0 && !json_object_is_type(val, json_type_string)) {
            return 0;
        }
        if (strcmp(key, "date") == 0 && !json_object_is_type(val, json_type_string)) {
            return 0;
        }
        if (strcmp(key, "location") == 0 && !json_object_is_type(val, json_type_string)) {
            return 0;
        }
    }
    return 1;
}

Event* deserialize_event(const char *json_str) {
    json_object *jobj = json_tokener_parse(json_str);
    if (!jobj) {
        return NULL;
    }

    if (!validate_event_schema(jobj)) {
        json_object_put(jobj);
        return NULL;
    }

    Event *event = (Event*)malloc(sizeof(Event));
    if (!event) {
        json_object_put(jobj);
        return NULL;
    }

    json_object *jevent = json_object_object_get(jobj, "event");
    json_object *jdate = json_object_object_get(jobj, "date");
    json_object *jlocation = json_object_object_get(jobj, "location");

    strcpy(event->event, json_object_get_string(jevent));
    strcpy(event->date, json_object_get_string(jdate));
    strcpy(event->location, json_object_get_string(jlocation));

    json_object_put(jobj);
    return event;
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    printf("Enter JSON string: ");
    fgets(buffer, MAX_BUFFER_SIZE, stdin);

    Event *event = deserialize_event(buffer);
    if (event) {
        printf("Event: %s, Date: %s, Location: %s\n", event->event, event->date, event->location);
        free(event);
    } else {
        printf("Invalid JSON or schema\n");
    }

    return 0;
}