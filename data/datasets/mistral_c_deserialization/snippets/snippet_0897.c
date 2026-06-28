#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char name[50];
    char breed[50];
    int age;
} Pet;

int validate_pet_schema(json_object *jobj) {
    json_object_object_foreach(jobj, key, val) {
        if (strcmp(key, "name") == 0 && !json_object_is_type(val, json_type_string)) {
            return 0;
        }
        if (strcmp(key, "breed") == 0 && !json_object_is_type(val, json_type_string)) {
            return 0;
        }
        if (strcmp(key, "age") == 0 && !json_object_is_type(val, json_type_int)) {
            return 0;
        }
    }
    return 1;
}

Pet* deserialize_pet(const char *json_str) {
    json_object *jobj = json_tokener_parse(json_str);
    if (!jobj) {
        return NULL;
    }

    if (!validate_pet_schema(jobj)) {
        json_object_put(jobj);
        return NULL;
    }

    Pet *pet = (Pet*)malloc(sizeof(Pet));
    if (!pet) {
        json_object_put(jobj);
        return NULL;
    }

    json_object *jname = json_object_object_get(jobj, "name");
    json_object *jbreed = json_object_object_get(jobj, "breed");
    json_object *jage = json_object_object_get(jobj, "age");

    strcpy(pet->name, json_object_get_string(jname));
    strcpy(pet->breed, json_object_get_string(jbreed));
    pet->age = json_object_get_int(jage);

    json_object_put(jobj);
    return pet;
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    printf("Enter JSON string: ");
    fgets(buffer, MAX_BUFFER_SIZE, stdin);

    Pet *pet = deserialize_pet(buffer);
    if (pet) {
        printf("Name: %s, Breed: %s, Age: %d\n", pet->name, pet->breed, pet->age);
        free(pet);
    } else {
        printf("Invalid JSON or schema\n");
    }

    return 0;
}