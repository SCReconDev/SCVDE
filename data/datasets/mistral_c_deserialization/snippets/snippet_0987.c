#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *command;
    int priority;
} Command;

void deserialize_command(const char *json_str, Command *cmd) {
    struct json_object *parsed_json;
    struct json_object *command;
    struct json_object *priority;

    parsed_json = json_tokener_parse(json_str);

    if (json_object_object_get_ex(parsed_json, "command", &command)) {
        cmd->command = strdup(json_object_get_string(command));
    }

    if (json_object_object_get_ex(parsed_json, "priority", &priority)) {
        cmd->priority = json_object_get_int(priority);
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"command\":\"restore\",\"priority\":1}";
    Command cmd;

    deserialize_command(json_str, &cmd);

    printf("Command: %s\n", cmd.command);
    printf("Priority: %d\n", cmd.priority);

    free(cmd.command);

    return 0;
}