#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char command_id[50];
    char command_name[50];
    char command_args[100];
} CommandInfo;

int validate_command_info(CommandInfo *command_info) {
    if (strlen(command_info->command_id) == 0 || strlen(command_info->command_name) == 0 || strlen(command_info->command_args) == 0) {
        return 0;
    }
    return 1;
}

CommandInfo* deserialize_command_info(const char *json_str) {
    struct json_object *parsed_json;
    struct json_object *command_id_obj, *command_name_obj, *command_args_obj;
    CommandInfo *command_info = (CommandInfo*)malloc(sizeof(CommandInfo));

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        free(command_info);
        return NULL;
    }

    json_object_object_get_ex(parsed_json, "command_id", &command_id_obj);
    json_object_object_get_ex(parsed_json, "command_name", &command_name_obj);
    json_object_object_get_ex(parsed_json, "command_args", &command_args_obj);

    if (command_id_obj == NULL || command_name_obj == NULL || command_args_obj == NULL) {
        json_object_put(parsed_json);
        free(command_info);
        return NULL;
    }

    strncpy(command_info->command_id, json_object_get_string(command_id_obj), sizeof(command_info->command_id) - 1);
    strncpy(command_info->command_name, json_object_get_string(command_name_obj), sizeof(command_info->command_name) - 1);
    strncpy(command_info->command_args, json_object_get_string(command_args_obj), sizeof(command_info->command_args) - 1);

    json_object_put(parsed_json);

    if (!validate_command_info(command_info)) {
        free(command_info);
        return NULL;
    }

    return command_info;
}

void process_command_info(CommandInfo *command_info) {
    printf("Command ID: %s\n", command_info->command_id);
    printf("Command Name: %s\n", command_info->command_name);
    printf("Command Args: %s\n", command_info->command_args);
}

int main() {
    char json_str[MAX_BUFFER_SIZE];
    CommandInfo *command_info;

    printf("Enter command info data in JSON format:\n");
    fgets(json_str, MAX_BUFFER_SIZE, stdin);

    command_info = deserialize_command_info(json_str);
    if (command_info == NULL) {
        printf("Invalid command info data\n");
        return 1;
    }

    process_command_info(command_info);
    free(command_info);

    return 0;
}