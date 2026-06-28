#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* command;
    int timeout;
} RestoreCommand;

void deserialize_restore_command(const char* json_str, RestoreCommand* command) {
    struct json_object* parsed_json;
    struct json_object* command_name;
    struct json_object* timeout;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "command", &command_name);
    json_object_object_get_ex(parsed_json, "timeout", &timeout);

    if (command_name != NULL && json_object_get_type(command_name) == json_type_string) {
        command->command = strdup(json_object_get_string(command_name));
    }

    if (timeout != NULL && json_object_get_type(timeout) == json_type_int) {
        command->timeout = json_object_get_int(timeout);
    }

    json_object_put(parsed_json);
}

void execute_restore(const char* input_file) {
    RestoreCommand command = {NULL, 0};
    deserialize_restore_command(input_file, &command);

    if (command.command != NULL) {
        printf("Command: %s\n", command.command);
        free(command.command);
    }

    printf("Timeout: %d\n", command.timeout);
}

int main() {
    const char* input_file = "{\"command\":\"restore_db\",\"timeout\":60}";
    execute_restore(input_file);
    return 0;
}