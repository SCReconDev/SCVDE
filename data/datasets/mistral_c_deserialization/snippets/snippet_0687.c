#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_FILE_SIZE 1024

typedef struct {
    char command[50];
    int timeout;
} Command;

int validate_command(json_object *jobj) {
    json_object *jcommand, *jtimeout;

    if (!json_object_object_get_ex(jobj, "command", &jcommand) ||
        !json_object_object_get_ex(jobj, "timeout", &jtimeout)) {
        return 0;
    }

    if (json_object_get_type(jcommand) != json_type_string ||
        json_object_get_type(jtimeout) != json_type_int) {
        return 0;
    }

    return 1;
}

Command* load_command(const char *file_content) {
    json_object *jobj = json_tokener_parse(file_content);
    if (jobj == NULL) {
        return NULL;
    }

    if (!validate_command(jobj)) {
        json_object_put(jobj);
        return NULL;
    }

    Command *command = (Command*)malloc(sizeof(Command));
    if (command == NULL) {
        json_object_put(jobj);
        return NULL;
    }

    strcpy(command->command, json_object_get_string(json_object_object_get(jobj, "command")));
    command->timeout = json_object_get_int(json_object_object_get(jobj, "timeout"));

    json_object_put(jobj);
    return command;
}

int main() {
    char file_content[MAX_FILE_SIZE];
    printf("Enter file content: ");
    fgets(file_content, MAX_FILE_SIZE, stdin);

    Command *command = load_command(file_content);
    if (command != NULL) {
        printf("Command: %s\nTimeout: %d\n", command->command, command->timeout);
        free(command);
    } else {
        printf("Invalid file content.\n");
    }

    return 0;
}