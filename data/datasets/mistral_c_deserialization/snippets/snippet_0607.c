#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* command;
    char* argument;
} Command;

void process_command(Command* command) {
    printf("Command: %s\n", command->command);
    printf("Argument: %s\n", command->argument);
}

Command* deserialize_command(const char* json_str) {
    struct json_object* parsed_json;
    struct json_object* command_obj;
    struct json_object* argument_obj;
    Command* command = malloc(sizeof(Command));

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        free(command);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "command", &command_obj);
    json_object_object_get_ex(parsed_json, "argument", &argument_obj);

    if (command_obj == NULL || argument_obj == NULL) {
        fprintf(stderr, "Invalid JSON format\n");
        json_object_put(parsed_json);
        free(command);
        return NULL;
    }

    command->command = strdup(json_object_get_string(command_obj));
    command->argument = strdup(json_object_get_string(argument_obj));

    json_object_put(parsed_json);
    return command;
}

int main() {
    const char* json_str = "{\"command\":\"restore\",\"argument\":\"backup.db\"}";
    Command* command = deserialize_command(json_str);

    if (command != NULL) {
        process_command(command);
        free(command->command);
        free(command->argument);
        free(command);
    }

    return 0;
}