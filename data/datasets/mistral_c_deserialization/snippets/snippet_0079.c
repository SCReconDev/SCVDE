#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char command[50];
    char args[200];
} Command;

void load_command(Command *cmd, const char *input) {
    sscanf(input, "%49s %199[^\n]", cmd->command, cmd->args);
}

void restore_state(const char *input) {
    Command cmd;
    load_command(&cmd, input);
    printf("Restored command: %s, args: %s\n", cmd.command, cmd.args);
}

int main() {
    char input[300];
    printf("Enter input file content: ");
    fgets(input, sizeof(input), stdin);
    restore_state(input);
    return 0;
}