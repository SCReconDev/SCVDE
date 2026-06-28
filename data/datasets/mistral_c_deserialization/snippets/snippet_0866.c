#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <cjson/cJSON.h>

typedef struct {
    char* event_id;
    char* event_name;
    char* event_date;
} Event;

bool validate_event_schema(const cJSON* json) {
    if (!cJSON_IsObject(json)) return false;
    cJSON* event_id = cJSON_GetObjectItemCaseSensitive(json, "event_id");
    cJSON* event_name = cJSON_GetObjectItemCaseSensitive(json, "event_name");
    cJSON* event_date = cJSON_GetObjectItemCaseSensitive(json, "event_date");
    if (!cJSON_IsString(event_id) || !cJSON_IsString(event_name) || !cJSON_IsString(event_date)) return false;
    return true;
}

Event* deserialize_event(const char* json_str) {
    cJSON* json = cJSON_Parse(json_str);
    if (!json || !validate_event_schema(json)) {
        cJSON_Delete(json);
        return NULL;
    }

    Event* event = malloc(sizeof(Event));
    if (!event) {
        cJSON_Delete(json);
        return NULL;
    }

    cJSON* event_id = cJSON_GetObjectItemCaseSensitive(json, "event_id");
    cJSON* event_name = cJSON_GetObjectItemCaseSensitive(json, "event_name");
    cJSON* event_date = cJSON_GetObjectItemCaseSensitive(json, "event_date");

    event->event_id = strdup(event_id->valuestring);
    event->event_name = strdup(event_name->valuestring);
    event->event_date = strdup(event_date->valuestring);

    cJSON_Delete(json);
    return event;
}

void free_event(Event* event) {
    if (event) {
        free(event->event_id);
        free(event->event_name);
        free(event->event_date);
        free(event);
    }
}

int main() {
    const char* json_str = "{\"event_id\":\"54321\",\"event_name\":\"Conference\",\"event_date\":\"2023-10-15\"}";
    Event* event = deserialize_event(json_str);

    if (event) {
        printf("Event ID: %s\nEvent Name: %s\nEvent Date: %s\n", event->event_id, event->event_name, event->event_date);
        free_event(event);
    } else {
        printf("Failed to deserialize event.\n");
    }

    return 0;
}