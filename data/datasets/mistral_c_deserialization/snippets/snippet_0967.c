#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* command_name;
    char* command_args;
} Command;

void deserialize_command(const char* json_str, Command* command) {
    struct json_object* parsed_json;
    struct json_object* command_name;
    struct json_object* command_args;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "command_name", &command_name);
    json_object_object_get_ex(parsed_json, "command_args", &command_args);

    if (command_name != NULL && json_object_is_type(command_name, json_type_string)) {
        command->command_name = strdup(json_object_get_string(command_name));
    }

    if (command_args != NULL && json_object_is_type(command_args, json_type_string)) {
        command->command_args = strdup(json_object_get_string(command_args));
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"command_name\":\"restore\",\"command_args\":\"--input=backup.json\"}";
    Command command;

    deserialize_command(json_str, &command);

    printf("Command Name: %s\n", command.command_name);
    printf("Command Args: %s\n", command.command_args);

    free(command.command_name);
    free(command.command_args);
    return 0;
}