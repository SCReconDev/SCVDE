#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *command;
    char *args;
} Command;

void deserialize_command(const char *json_str, Command *cmd) {
    struct json_object *parsed_json;
    struct json_object *command;
    struct json_object *args;

    parsed_json = json_tokener_parse(json_str);

    if (json_object_object_get_ex(parsed_json, "command", &command)) {
        cmd->command = strdup(json_object_get_string(command));
    }

    if (json_object_object_get_ex(parsed_json, "args", &args)) {
        cmd->args = strdup(json_object_get_string(args));
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"command\":\"restore\",\"args\":\"--file=backup.json\"}";
    Command cmd;

    deserialize_command(json_str, &cmd);

    printf("Command: %s\n", cmd.command);
    printf("Args: %s\n", cmd.args);

    free(cmd.command);
    free(cmd.args);

    return 0;
}