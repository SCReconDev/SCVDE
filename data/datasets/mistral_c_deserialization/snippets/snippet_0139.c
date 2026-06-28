#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char command[50];
    char args[100];
} Command;

void load_command(Command *cmd, const char *input) {
    sscanf(input, "%49s %99[^\n]", cmd->command, cmd->args);
}

void restore_command(const char *input) {
    Command cmd;
    load_command(&cmd, input);
    printf("Command: %s, Args: %s\n", cmd.command, cmd.args);
}

int main() {
    char input[150];
    printf("Enter command input: ");
    fgets(input, sizeof(input), stdin);
    restore_command(input);
    return 0;
}