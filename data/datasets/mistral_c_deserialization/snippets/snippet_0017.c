#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* command;
    int repeat;
} CLICommand;

void deserialize_cli_command(CLICommand* command, const char* data) {
    char* token = strtok((char*)data, " ");
    command->command = strdup(token);
    token = strtok(NULL, " ");
    command->repeat = atoi(token);
}

void restore_command(const char* input_file_data) {
    CLICommand command;
    deserialize_cli_command(&command, input_file_data);
    printf("CLI Command - Command: %s, Repeat: %d\n", command.command, command.repeat);
    free(command.command);
}

int main() {
    const char* input_file_data = "backup 3";
    restore_command(input_file_data);
    return 0;
}