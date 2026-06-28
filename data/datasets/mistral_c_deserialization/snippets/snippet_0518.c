#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char name[50];
    char type[50];
    int level;
} Character;

void display_character(Character *character) {
    printf("Name: %s\n", character->name);
    printf("Type: %s\n", character->type);
    printf("Level: %d\n", character->level);
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    FILE *file = fopen("character.json", "r");
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

    struct json_object *name_obj, *type_obj, *level_obj;
    if (!json_object_object_get_ex(parsed_json, "name", &name_obj) ||
        !json_object_object_get_ex(parsed_json, "type", &type_obj) ||
        !json_object_object_get_ex(parsed_json, "level", &level_obj)) {
        fprintf(stderr, "Error accessing JSON fields\n");
        json_object_put(parsed_json);
        return 1;
    }

    Character character;
    strncpy(character.name, json_object_get_string(name_obj), sizeof(character.name) - 1);
    strncpy(character.type, json_object_get_string(type_obj), sizeof(character.type) - 1);
    character.level = json_object_get_int(level_obj);

    display_character(&character);

    json_object_put(parsed_json);
    return 0;
}