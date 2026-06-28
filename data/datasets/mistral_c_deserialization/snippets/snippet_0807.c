#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

typedef struct {
    char *command;
    char *arguments;
} CommandData;

void deserialize_command_data(const char *json_str, CommandData *command_data) {
    struct json_object *parsed_json;
    struct json_object *command_obj, *arguments_obj;

    parsed_json = json_tokener_parse(json_str);
    if (parsed_json == NULL) {
        fprintf(stderr, "Error parsing JSON\n");
        return;
    }

    json_object_object_get_ex(parsed_json, "command", &command_obj);
    json_object_object_get_ex(parsed_json, "arguments", &arguments_obj);

    if (command_obj != NULL && json_object_get_type(command_obj) == json_type_string) {
        command_data->command = strdup(json_object_get_string(command_obj));
    }

    if (arguments_obj != NULL && json_object_get_type(arguments_obj) == json_type_string) {
        command_data->arguments = strdup(json_object_get_string(arguments_obj));
    }

    json_object_put(parsed_json);
}

int main() {
    const char *json_str = "{\"command\":\"backup\",\"arguments\":\"--all --verbose\"}";
    CommandData command_data;

    deserialize_command_data(json_str, &command_data);

    printf("Command: %s\n", command_data.command);
    printf("Arguments: %s\n", command_data.arguments);

    free(command_data.command);
    free(command_data.arguments);
    return 0;
}