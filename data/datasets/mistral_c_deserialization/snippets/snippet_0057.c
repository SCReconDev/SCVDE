#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* command;
    char* args;
} Command;

void deserialize_command(const char* input, Command* cmd) {
    char* token = strtok((char*)input, " ");
    cmd->command = strdup(token);

    token = strtok(NULL, " ");
    cmd->args = strdup(token);
}

int main() {
    const char* input = "restore backup.db";
    Command cmd;

    deserialize_command(input, &cmd);

    printf("Command: %s, Args: %s\n", cmd.command, cmd.args);

    free(cmd.command);
    free(cmd.args);
    return 0;
}