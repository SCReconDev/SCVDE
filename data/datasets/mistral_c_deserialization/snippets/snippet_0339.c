#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char command[50];
    char args[100];
} RestoreCommand;

void deserialize_command(const char* data, RestoreCommand* cmd) {
    sscanf(data, "%49s %99[^\n]", cmd->command, cmd->args);
}

void execute_restore_command(const char* data) {
    RestoreCommand cmd;
    deserialize_command(data, &cmd);
    printf("Command: %s, Args: %s\n", cmd.command, cmd.args);
}

int main() {
    char data[200];
    printf("Enter restore command data: ");
    fgets(data, sizeof(data), stdin);
    execute_restore_command(data);
    return 0;
}