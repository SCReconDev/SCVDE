#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* command;
    char* args;
} Command;

void parse_command(Command* cmd, const char* input) {
    char* token = strtok((char*)input, " ");
    cmd->command = strdup(token);
    token = strtok(NULL, " ");
    cmd->args = strdup(token);
}

int main() {
    char* input = "restore backup.db";
    Command cmd;
    parse_command(&cmd, input);
    printf("Command: %s, Args: %s\n", cmd.command, cmd.args);
    free(cmd.command);
    free(cmd.args);
    return 0;
}