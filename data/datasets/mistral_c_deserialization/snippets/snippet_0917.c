#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <json-c/json.h>

typedef struct {
    char* command_name;
    char* command_value;
} Command;

bool validate_command_json(const char* json_str) {
    struct json_object* obj = json_tokener_parse(json_str);
    if (obj == NULL) {
        return false;
    }

    bool has_command_name = json_object_object_get_ex(obj, "command_name", NULL);
    bool has_command_value = json_object_object_get_ex(obj, "command_value", NULL);

    json_object_put(obj);
    return has_command_name && has_command_value;
}

Command* deserialize_command(const char* json_str) {
    if (!validate_command_json(json_str)) {
        return NULL;
    }

    struct json_object* obj = json_tokener_parse(json_str);
    Command* command = malloc(sizeof(Command));

    struct json_object* command_name_obj;
    json_object_object_get_ex(obj, "command_name", &command_name_obj);
    command->command_name = strdup(json_object_get_string(command_name_obj));

    struct json_object* command_value_obj;
    json_object_object_get_ex(obj, "command_value", &command_value_obj);
    command->command_value = strdup(json_object_get_string(command_value_obj));

    json_object_put(obj);
    return command;
}

void free_command(Command* command) {
    free(command->command_name);
    free(command->command_value);
    free(command);
}

void restore_command(const char* json_str) {
    Command* command = deserialize_command(json_str);
    if (command == NULL) {
        printf("Invalid command data\n");
        return;
    }

    printf("Command Name: %s, Command Value: %s\n", command->command_name, command->command_value);
    free_command(command);
}

int main() {
    const char* json_str = "{\"command_name\":\"backup\",\"command_value\":\"start\"}";
    restore_command(json_str);
    return 0;
}