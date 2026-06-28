#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *name;
    char *type;
    int level;
} Character;

void deserialize_character(const char *json_str, Character *character) {
    struct json_object *parsed_json;
    struct json_object *name;
    struct json_object *type;
    struct json_object *level;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "name", &name);
    json_object_object_get_ex(parsed_json, "type", &type);
    json_object_object_get_ex(parsed_json, "level", &level);

    if (name != NULL && json_object_is_type(name, json_type_string)) {
        character->name = strdup(json_object_get_string(name));
    } else {
        character->name = NULL;
    }

    if (type != NULL && json_object_is_type(type, json_type_string)) {
        character->type = strdup(json_object_get_string(type));
    } else {
        character->type = NULL;
    }

    if (level != NULL && json_object_is_type(level, json_type_int)) {
        character->level = json_object_get_int(level);
    } else {
        character->level = 0;
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"name\":\"Warrior\",\"type\":\"Human\",\"level\":10}";
    Character character;

    deserialize_character(json_str, &character);

    printf("Name: %s\n", character.name);
    printf("Type: %s\n", character.type);
    printf("Level: %d\n", character.level);

    free(character.name);
    free(character.type);
    return 0;
}