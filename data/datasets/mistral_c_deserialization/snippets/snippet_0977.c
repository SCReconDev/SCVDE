#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* command;
    char* arguments;
} Command;

void deserialize_command(const char* json_str, Command* cmd) {
    struct json_object* parsed_json;
    struct json_object* command;
    struct json_object* arguments;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "command", &command)) {
        fprintf(stderr, "Error: 'command' field not found\n");
        json_object_put(parsed_json);
        return;
    }

    if (!json_object_object_get_ex(parsed_json, "arguments", &arguments)) {
        fprintf(stderr, "Error: 'arguments' field not found\n");
        json_object_put(parsed_json);
        return;
    }

    cmd->command = strdup(json_object_get_string(command));
    cmd->arguments = strdup(json_object_get_string(arguments));

    json_object_put(parsed_json);
}

int main() {
    const char* json_str = "{\"command\":\"restore\",\"arguments\":\"--file=backup.json\"}";
    Command cmd;

    deserialize_command(json_str, &cmd);

    printf("Command: %s\n", cmd.command);
    printf("Arguments: %s\n", cmd.arguments);

    free(cmd.command);
    free(cmd.arguments);
    return 0;
}