#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char command[50];
    char arguments[200];
} Command;

int deserialize_command(const char* json_str, Command* command) {
    struct json_object *parsed_json;
    struct json_object *command_obj, *arguments_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return -1;
    }

    if (!json_object_object_get_ex(parsed_json, "command", &command_obj)) {
        fprintf(stderr, "Error getting command\n");
        json_object_put(parsed_json);
        return -1;
    }

    if (!json_object_object_get_ex(parsed_json, "arguments", &arguments_obj)) {
        fprintf(stderr, "Error getting arguments\n");
        json_object_put(parsed_json);
        return -1;
    }

    strncpy(command->command, json_object_get_string(command_obj), sizeof(command->command) - 1);
    strncpy(command->arguments, json_object_get_string(arguments_obj), sizeof(command->arguments) - 1);

    json_object_put(parsed_json);
    return 0;
}

int main() {
    char buffer[MAX_BUFFER_SIZE];
    Command command;

    printf("Enter command JSON: ");
    fgets(buffer, sizeof(buffer), stdin);

    if (deserialize_command(buffer, &command) == 0) {
        printf("Deserialized Command: Command=%s, Arguments=%s\n", command.command, command.arguments);
    } else {
        fprintf(stderr, "Failed to deserialize command\n");
    }

    return 0;
}