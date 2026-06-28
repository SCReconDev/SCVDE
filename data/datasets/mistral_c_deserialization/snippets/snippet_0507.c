#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

typedef struct {
    char* command;
    char* args;
} Command;

void restore_command(const char* input_file) {
    cJSON* json = cJSON_Parse(input_file);
    if (json == NULL) {
        const char* error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return;
    }

    cJSON* command = cJSON_GetObjectItemCaseSensitive(json, "command");
    cJSON* args = cJSON_GetObjectItemCaseSensitive(json, "args");

    if (cJSON_IsString(command) && (command->valuestring != NULL) && cJSON_IsString(args) && (args->valuestring != NULL)) {
        Command cmd;
        cmd.command = strdup(command->valuestring);
        cmd.args = strdup(args->valuestring);

        printf("Command: %s, Args: %s\n", cmd.command, cmd.args);

        free(cmd.command);
        free(cmd.args);
    }

    cJSON_Delete(json);
}

int main() {
    const char* input_file = "{\"command\":\"backup\",\"args\":\"--all\"}";
    restore_command(input_file);
    return 0;
}