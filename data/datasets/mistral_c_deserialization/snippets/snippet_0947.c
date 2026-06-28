#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* command_name;
    char* command_args;
} Command;

void parse_command_input(const char* input) {
    cJSON* json = cJSON_Parse(input);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return;
    }

    cJSON* command_name = cJSON_GetObjectItemCaseSensitive(json, "command_name");
    cJSON* command_args = cJSON_GetObjectItemCaseSensitive(json, "command_args");

    if (cJSON_IsString(command_name) && (command_name->valuestring != NULL)) {
        printf("Command Name: %s\n", command_name->valuestring);
    }

    if (cJSON_IsString(command_args) && (command_args->valuestring != NULL)) {
        printf("Command Args: %s\n", command_args->valuestring);
    }

    cJSON_Delete(json);
}

int main() {
    const char* input = "{\"command_name\":\"restore\",\"command_args\":\"--file example.txt\"}";
    parse_command_input(input);
    return 0;
}