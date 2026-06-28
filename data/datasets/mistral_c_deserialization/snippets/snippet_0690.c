#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_PREFERENCES_SIZE 1024

typedef struct {
    char preference_name[50];
    int preference_value;
} Preference;

int validate_preference(json_object *jobj) {
    json_object *jpreference_name, *jpreference_value;

    if (!json_object_object_get_ex(jobj, "preference_name", &jpreference_name) ||
        !json_object_object_get_ex(jobj, "preference_value", &jpreference_value)) {
        return 0;
    }

    if (json_object_get_type(jpreference_name) != json_type_string ||
        json_object_get_type(jpreference_value) != json_type_int) {
        return 0;
    }

    return 1;
}

Preference* import_preference(const char *preference_data) {
    json_object *jobj = json_tokener_parse(preference_data);
    if (jobj == NULL) {
        return NULL;
    }

    if (!validate_preference(jobj)) {
        json_object_put(jobj);
        return NULL;
    }

    Preference *preference = (Preference*)malloc(sizeof(Preference));
    if (preference == NULL) {
        json_object_put(jobj);
        return NULL;
    }

    strcpy(preference->preference_name, json_object_get_string(json_object_object_get(jobj, "preference_name")));
    preference->preference_value = json_object_get_int(json_object_object_get(jobj, "preference_value"));

    json_object_put(jobj);
    return preference;
}

int main() {
    char preference_data[MAX_PREFERENCES_SIZE];
    printf("Enter preference data: ");
    fgets(preference_data, MAX_PREFERENCES_SIZE, stdin);

    Preference *preference = import_preference(preference_data);
    if (preference != NULL) {
        printf("Preference Name: %s\nPreference Value: %d\n", preference->preference_name, preference->preference_value);
        free(preference);
    } else {
        printf("Invalid preference data.\n");
    }

    return 0;
}