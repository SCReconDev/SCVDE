#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <json-c/json.h>

typedef struct {
    char *event_id;
    char *event_name;
    char *event_date;
} Event;

bool validate_event_schema(const json_object *jobj) {
    json_object_object_foreach(jobj, key, val) {
        if (strcmp(key, "event_id") == 0 && json_object_get_type(val) != json_type_string) {
            return false;
        }
        if (strcmp(key, "event_name") == 0 && json_object_get_type(val) != json_type_string) {
            return false;
        }
        if (strcmp(key, "event_date") == 0 && json_object_get_type(val) != json_type_string) {
            return false;
        }
    }
    return true;
}

Event *deserialize_event(const char *json_str) {
    json_object *jobj = json_tokener_parse(json_str);
    if (!jobj) {
        return NULL;
    }

    if (!validate_event_schema(jobj)) {
        json_object_put(jobj);
        return NULL;
    }

    Event *event = malloc(sizeof(Event));
    if (!event) {
        json_object_put(jobj);
        return NULL;
    }

    json_object *event_id_obj, *event_name_obj, *event_date_obj;
    if (json_object_object_get_ex(jobj, "event_id", &event_id_obj)) {
        event->event_id = strdup(json_object_get_string(event_id_obj));
    } else {
        event->event_id = NULL;
    }

    if (json_object_object_get_ex(jobj, "event_name", &event_name_obj)) {
        event->event_name = strdup(json_object_get_string(event_name_obj));
    } else {
        event->event_name = NULL;
    }

    if (json_object_object_get_ex(jobj, "event_date", &event_date_obj)) {
        event->event_date = strdup(json_object_get_string(event_date_obj));
    } else {
        event->event_date = NULL;
    }

    json_object_put(jobj);
    return event;
}

void free_event(Event *event) {
    if (event) {
        free(event->event_id);
        free(event->event_name);
        free(event->event_date);
        free(event);
    }
}

int main() {
    const char *json_str = "{\"event_id\":\"54321\",\"event_name\":\"Conference\",\"event_date\":\"2023-12-15\"}";
    Event *event = deserialize_event(json_str);

    if (event) {
        printf("Event ID: %s\n", event->event_id);
        printf("Event Name: %s\n", event->event_name);
        printf("Event Date: %s\n", event->event_date);
        free_event(event);
    } else {
        printf("Failed to deserialize event.\n");
    }

    return 0;
}