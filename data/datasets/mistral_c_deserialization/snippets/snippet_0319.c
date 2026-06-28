#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* command;
    char* arguments;
} Command;

void restore_command(const char* data, Command* cmd) {
    char* token = strtok((char*)data, " ");
    cmd->command = strdup(token);
    token = strtok(NULL, " ");
    cmd->arguments = strdup(token);
}

int main() {
    char* command_data = "backup /home/user/data";
    Command cmd;
    restore_command(command_data, &cmd);
    printf("Command: %s, Arguments: %s\n", cmd.command, cmd.arguments);
    free(cmd.command);
    free(cmd.arguments);
    return 0;
}