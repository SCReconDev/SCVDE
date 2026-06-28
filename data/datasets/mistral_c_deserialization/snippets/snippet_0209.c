#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char command[50];
    char args[100];
} CLICommand;

void load_command(CLICommand *cmd, const char *data) {
    sscanf(data, "%49s %99[^\n]", cmd->command, cmd->args);
}

void restore_command(const char *data) {
    CLICommand cmd;
    load_command(&cmd, data);
    printf("Command: %s, Args: %s\n", cmd.command, cmd.args);
}

int main() {
    char data[200];
    printf("Enter command data: ");
    fgets(data, sizeof(data), stdin);
    restore_command(data);
    return 0;
}