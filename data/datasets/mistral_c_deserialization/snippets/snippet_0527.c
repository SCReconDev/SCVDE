#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char command_name[MAX_BUFFER_SIZE];
    char command_args[MAX_BUFFER_SIZE];
} Command;

void execute_restore_command(const char* json_data) {
    struct json_object *parsed_json;
    struct json_object *command_name_obj, *command_args_obj;
    Command command;

    parsed_json = json_tokener_parse(json_data);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON data\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "command_name", &command_name_obj) ||
        !json_object_object_get_ex(parsed_json, "command_args", &command_args_obj)) {
        fprintf(stderr, "Error: Missing required fields in JSON data\n");
        json_object_put(parsed_json);
        return;
    }

    strncpy(command.command_name, json_object_get_string(command_name_obj), MAX_BUFFER_SIZE - 1);
    strncpy(command.command_args, json_object_get_string(command_args_obj), MAX_BUFFER_SIZE - 1);

    printf("Command Name: %s, Command Args: %s\n", command.command_name, command.command_args);

    json_object_put(parsed_json);
}

int main() {
    const char* json_data = "{\"command_name\":\"restore\",\"command_args\":\"backup_file\"}";
    execute_restore_command(json_data);
    return 0;
}