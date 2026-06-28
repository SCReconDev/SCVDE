#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char command[MAX_BUFFER_SIZE];
    char arguments[MAX_BUFFER_SIZE];
} CLICommand;

void parse_cli_command(const char *json_str, CLICommand *command) {
    struct json_object *parsed_json;
    struct json_object *command_obj;
    struct json_object *arguments_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "command", &command_obj);
    if (command_obj != NULL) {
        strncpy(command->command, json_object_get_string(command_obj), MAX_BUFFER_SIZE - 1);
    }

    json_object_object_get_ex(parsed_json, "arguments", &arguments_obj);
    if (arguments_obj != NULL) {
        strncpy(command->arguments, json_object_get_string(arguments_obj), MAX_BUFFER_SIZE - 1);
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"command\":\"restore\",\"arguments\":\"--file=backup.json\"}";
    CLICommand command;

    parse_cli_command(json_str, &command);

    printf("Command: %s\n", command.command);
    printf("Arguments: %s\n", command.arguments);

    return 0;
}