#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* command;
    char* arguments;
} Command;

void deserialize_command(const char* json_str, Command* command) {
    struct json_object* parsed_json;
    struct json_object* command_obj;
    struct json_object* arguments_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "command", &command_obj);
    json_object_object_get_ex(parsed_json, "arguments", &arguments_obj);

    if (command_obj != NULL && json_object_is_type(command_obj, json_type_string)) {
        command->command = strdup(json_object_get_string(command_obj));
    }

    if (arguments_obj != NULL && json_object_is_type(arguments_obj, json_type_string)) {
        command->arguments = strdup(json_object_get_string(arguments_obj));
    }

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"command\":\"restore\",\"arguments\":\"--file backup.dat\"}";
    Command command;

    deserialize_command(json_str, &command);

    printf("Command: %s\n", command.command);
    printf("Arguments: %s\n", command.arguments);

    free(command.command);
    free(command.arguments);
    return 0;
}