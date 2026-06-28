#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <cjson/cJSON.h>

typedef struct {
    char* command;
    char* arguments;
    int timeout;
} Command;

bool validate_command_schema(cJSON* json) {
    if (!cJSON_HasObjectItem(json, "command") ||
        !cJSON_HasObjectItem(json, "arguments") ||
        !cJSON_HasObjectItem(json, "timeout")) {
        return false;
    }

    cJSON* command = cJSON_GetObjectItemCaseSensitive(json, "command");
    cJSON* arguments = cJSON_GetObjectItemCaseSensitive(json, "arguments");
    cJSON* timeout = cJSON_GetObjectItemCaseSensitive(json, "timeout");

    if (!cJSON_IsString(command) || !cJSON_IsString(arguments) || !cJSON_IsNumber(timeout)) {
        return false;
    }

    return true;
}

Command* deserialize_command(const char* json_str) {
    cJSON* json = cJSON_Parse(json_str);
    if (!json) {
        return NULL;
    }

    if (!validate_command_schema(json)) {
        cJSON_Delete(json);
        return NULL;
    }

    Command* cmd = (Command*)malloc(sizeof(Command));
    if (!cmd) {
        cJSON_Delete(json);
        return NULL;
    }

    cJSON* command = cJSON_GetObjectItemCaseSensitive(json, "command");
    cJSON* arguments = cJSON_GetObjectItemCaseSensitive(json, "arguments");
    cJSON* timeout = cJSON_GetObjectItemCaseSensitive(json, "timeout");

    cmd->command = strdup(command->valuestring);
    cmd->arguments = strdup(arguments->valuestring);
    cmd->timeout = timeout->valueint;

    cJSON_Delete(json);

    return cmd;
}

void free_command(Command* cmd) {
    if (cmd) {
        free(cmd->command);
        free(cmd->arguments);
        free(cmd);
    }
}

int main() {
    const char* json_str = "{\"command\":\"restore\",\"arguments\":\"--file backup.dat\",\"timeout\":30}";
    Command* cmd = deserialize_command(json_str);

    if (cmd) {
        printf("Command: %s\n", cmd->command);
        printf("Arguments: %s\n", cmd->arguments);
        printf("Timeout: %d\n", cmd->timeout);
        free_command(cmd);
    } else {
        printf("Failed to deserialize command.\n");
    }

    return 0;
}