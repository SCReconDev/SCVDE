#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char command[50];
    char args[100];
} Command;

void load_command(const char* data, Command* cmd) {
    char* decoded_data = malloc(strlen(data) + 1);
    strcpy(decoded_data, data);
    sscanf(decoded_data, "%49s %99[^\n]", cmd->command, cmd->args);
    free(decoded_data);
}

void restore_state(const char* command_data) {
    Command cmd;
    load_command(command_data, &cmd);
    printf("Restored command: %s with args: %s\n", cmd.command, cmd.args);
}

int main() {
    const char* command_data = "backup --all";
    restore_state(command_data);
    return 0;
}