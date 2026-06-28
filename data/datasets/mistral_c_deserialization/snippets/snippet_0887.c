#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char* command;
    char* data;
} RestoreCommand;

void process_restore_command(RestoreCommand* cmd) {
    printf("Command: %s, Data: %s\n", cmd->command, cmd->data);
}

int main() {
    const char* input_file = "{\"command\":\"restore\",\"data\":\"{\\\"source\\\":\\\"backup.tar.gz\\\",\\\"destination\\\":\\\"/data/restore\\\"}\"}";
    struct json_object* parsed_json;
    struct json_object* command_obj;
    struct json_object* data_obj;
    RestoreCommand cmd;

    parsed_json = json_tokener_parse(input_file);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    if (!json_object_object_get_ex(parsed_json, "command", &command_obj) ||
        !json_object_object_get_ex(parsed_json, "data", &data_obj)) {
        fprintf(stderr, "Error extracting JSON fields\n");
        json_object_put(parsed_json);
        return 1;
    }

    cmd.command = strdup(json_object_get_string(command_obj));
    cmd.data = strdup(json_object_get_string(data_obj));

    process_restore_command(&cmd);

    free(cmd.command);
    free(cmd.data);
    json_object_put(parsed_json);

    return 0;
}