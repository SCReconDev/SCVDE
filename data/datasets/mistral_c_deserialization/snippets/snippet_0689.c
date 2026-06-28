#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_FIXTURE_SIZE 1024

typedef struct {
    char fixture_name[50];
    int value;
} Fixture;

int validate_fixture(json_object *jobj) {
    json_object *jfixture_name, *jvalue;

    if (!json_object_object_get_ex(jobj, "fixture_name", &jfixture_name) ||
        !json_object_object_get_ex(jobj, "value", &jvalue)) {
        return 0;
    }

    if (json_object_get_type(jfixture_name) != json_type_string ||
        json_object_get_type(jvalue) != json_type_int) {
        return 0;
    }

    return 1;
}

Fixture* load_fixture(const char *fixture_data) {
    json_object *jobj = json_tokener_parse(fixture_data);
    if (jobj == NULL) {
        return NULL;
    }

    if (!validate_fixture(jobj)) {
        json_object_put(jobj);
        return NULL;
    }

    Fixture *fixture = (Fixture*)malloc(sizeof(Fixture));
    if (fixture == NULL) {
        json_object_put(jobj);
        return NULL;
    }

    strcpy(fixture->fixture_name, json_object_get_string(json_object_object_get(jobj, "fixture_name")));
    fixture->value = json_object_get_int(json_object_object_get(jobj, "value"));

    json_object_put(jobj);
    return fixture;
}

int main() {
    char fixture_data[MAX_FIXTURE_SIZE];
    printf("Enter fixture data: ");
    fgets(fixture_data, MAX_FIXTURE_SIZE, stdin);

    Fixture *fixture = load_fixture(fixture_data);
    if (fixture != NULL) {
        printf("Fixture Name: %s\nValue: %d\n", fixture->fixture_name, fixture->value);
        free(fixture);
    } else {
        printf("Invalid fixture data.\n");
    }

    return 0;
}