#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *command;
    int priority;
} RestoreCommand;

void parse_restore_command(json_object *jobj, RestoreCommand *command) {
    json_object_object_foreach(jobj, key, val) {
        if (strcmp(key, "command") == 0) {
            command->command = strdup(json_object_get_string(val));
        } else if (strcmp(key, "priority") == 0) {
            command->priority = json_object_get_int(val);
        }
    }
}

int main() {
    const char *input_file = "{\"command\":\"restore\",\"priority\":1}";
    json_object *jobj = json_tokener_parse(input_file);

    if (jobj == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return 1;
    }

    RestoreCommand command;
    parse_restore_command(jobj, &command);

    printf("Command: %s\n", command.command);
    printf("Priority: %d\n", command.priority);

    free(command.command);
    json_object_put(jobj);

    return 0;
}