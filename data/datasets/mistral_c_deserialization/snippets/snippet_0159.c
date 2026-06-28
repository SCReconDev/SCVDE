#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* command;
    char* args;
} Command;

void restore_command(Command* cmd, const char* data) {
    char* token = strtok((char*)data, " ");
    cmd->command = strdup(token);
    token = strtok(NULL, " ");
    cmd->args = strdup(token);
}

int main() {
    char* cmd_data = "ls -l";
    Command cmd;
    restore_command(&cmd, cmd_data);
    printf("Command: %s, Args: %s\n", cmd.command, cmd.args);
    free(cmd.command);
    free(cmd.args);
    return 0;
}