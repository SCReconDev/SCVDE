#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_INPUT_SIZE 1024

typedef struct {
    char command_id[256];
    char command_name[256];
    char command_args[256];
} Command;

int validate_command(Command *command) {
    if (strlen(command->command_id) == 0 || strlen(command->command_name) == 0 || strlen(command->command_args) == 0) {
        return 0;
    }
    return 1;
}

Command* deserialize_command(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *command_id_obj, *command_name_obj, *command_args_obj;
    Command *command = malloc(sizeof(Command));

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        free(command);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "command_id", &command_id_obj);
    json_object_object_get_ex(parsed_json, "command_name", &command_name_obj);
    json_object_object_get_ex(parsed_json, "command_args", &command_args_obj);

    if (command_id_obj == NULL || command_name_obj == NULL || command_args_obj == NULL) {
        json_object_put(parsed_json);
        free(command);
        return NULL;
    }

    strncpy(command->command_id, json_object_get_string(command_id_obj), sizeof(command->command_id) - 1);
    strncpy(command->command_name, json_object_get_string(command_name_obj), sizeof(command->command_name) - 1);
    strncpy(command->command_args, json_object_get_string(command_args_obj), sizeof(command->command_args) - 1);

    json_object_put(parsed_json);

    if (!validate_command(command)) {
        free(command);
        return NULL;
    }

    return command;
}

void process_command(Command *command) {
    printf("Processing command: %s, %s, %s\n", command->command_id, command->command_name, command->command_args);
}

int main() {
    char input[MAX_INPUT_SIZE];
    Command *command;

    printf("Enter command data in JSON format: ");
    fgets(input, sizeof(input), stdin);

    command = deserialize_command(input);
    if (command == NULL) {
        printf("Invalid command data\n");
        return 1;
    }

    process_command(command);

    free(command);
    return 0;
}