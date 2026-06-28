#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* command;
    int args_count;
} Command;

void deserialize_command(char* data, Command* cmd) {
    char* token = strtok(data, " ");
    cmd->command = strdup(token);
    token = strtok(NULL, " ");
    cmd->args_count = atoi(token);
}

void restore_command(char* input_file) {
    Command cmd;
    deserialize_command(input_file, &cmd);
    printf("Command: %s, Args Count: %d\n", cmd.command, cmd.args_count);
    free(cmd.command);
}

int main() {
    char* input_file = "backup 2";
    restore_command(input_file);
    return 0;
}