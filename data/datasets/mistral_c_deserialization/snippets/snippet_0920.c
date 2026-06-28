#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <json-c/json.h>

typedef struct {
    char* pref_name;
    char* pref_value;
} Preference;

bool validate_pref_json(const char* json_str) {
    struct json_object* obj = json_tokener_parse(json_str);
    if (obj == NULL) {
        return false;
    }

    bool has_pref_name = json_object_object_get_ex(obj, "pref_name", NULL);
    bool has_pref_value = json_object_object_get_ex(obj, "pref_value", NULL);

    json_object_put(obj);
    return has_pref_name && has_pref_value;
}

Preference* deserialize_preference(const char* json_str) {
    if (!validate_pref_json(json_str)) {
        return NULL;
    }

    struct json_object* obj = json_tokener_parse(json_str);
    Preference* pref = malloc(sizeof(Preference));

    struct json_object* pref_name_obj;
    json_object_object_get_ex(obj, "pref_name", &pref_name_obj);
    pref->pref_name = strdup(json_object_get_string(pref_name_obj));

    struct json_object* pref_value_obj;
    json_object_object_get_ex(obj, "pref_value", &pref_value_obj);
    pref->pref_value = strdup(json_object_get_string(pref_value_obj));

    json_object_put(obj);
    return pref;
}

void free_preference(Preference* pref) {
    free(pref->pref_name);
    free(pref->pref_value);
    free(pref);
}

void import_preference(const char* json_str) {
    Preference* pref = deserialize_preference(json_str);
    if (pref == NULL) {
        printf("Invalid preference data\n");
        return;
    }

    printf("Preference Name: %s, Preference Value: %s\n", pref->pref_name, pref->pref_value);
    free_preference(pref);
}

int main() {
    const char* json_str = "{\"pref_name\":\"theme\",\"pref_value\":\"dark\"}";
    import_preference(json_str);
    return 0;
}