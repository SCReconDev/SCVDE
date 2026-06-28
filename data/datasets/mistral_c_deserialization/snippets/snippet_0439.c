#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* command;
    char* args;
} RestoreCommand;

void execute_restore(RestoreCommand* cmd) {
    printf("Executing restore command: %s %s\n", cmd->command, cmd->args);
}

int main() {
    char* input_file = "{\"command\":\"restore\",\"args\":\"--all\"}";
    RestoreCommand* cmd = (RestoreCommand*)malloc(sizeof(RestoreCommand));
    memcpy(cmd, input_file, sizeof(RestoreCommand));
    execute_restore(cmd);
    free(cmd);
    return 0;
}