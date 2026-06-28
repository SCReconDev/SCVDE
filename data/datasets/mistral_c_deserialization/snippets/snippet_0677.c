#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* command;
    char* arguments;
} CommandData;

void execute_command(CommandData* command) {
    printf("Command: %s, Arguments: %s\n", command->command, command->arguments);
}

int main() {
    const char* input_file = "{\"command\":\"run\",\"arguments\":\"--verbose\"}";
    struct json_object* json_obj = json_tokener_parse(input_file);

    if (json_obj == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    CommandData command;
    json_object_object_foreach(json_obj, key, val) {
        if (strcmp(key, "command") == 0) {
            command.command = strdup(json_object_get_string(val));
        } else if (strcmp(key, "arguments") == 0) {
            command.arguments = strdup(json_object_get_string(val));
        }
    }

    execute_command(&command);
    free(command.command);
    free(command.arguments);
    json_object_put(json_obj);

    return 0;
}