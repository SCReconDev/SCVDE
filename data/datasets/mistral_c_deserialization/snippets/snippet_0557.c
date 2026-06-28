#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* command;
    char* arguments;
} RestoreCommand;

void parse_input_file(const char* file_content) {
    struct json_object* parsed_json;
    struct json_object* command;
    struct json_object* arguments;

    parsed_json = json_tokener_parse(file_content);

    if (json_object_object_get_ex(parsed_json, "command", &command)) {
        RestoreCommand* restore_cmd = (RestoreCommand*)malloc(sizeof(RestoreCommand));
        restore_cmd->command = strdup(json_object_get_string(command));

        if (json_object_object_get_ex(parsed_json, "arguments", &arguments)) {
            restore_cmd->arguments = strdup(json_object_get_string(arguments));
        } else {
            restore_cmd->arguments = strdup("");
        }

        printf("Command: %s, Arguments: %s\n", restore_cmd->command, restore_cmd->arguments);
        free(restore_cmd->command);
        free(restore_cmd->arguments);
        free(restore_cmd);
    }

    json_object_put(parsed_json);
}

int main() {
    const char* file_content = "{\"command\":\"restore\",\"arguments\":\"--all\"}";
    parse_input_file(file_content);
    return 0;
}