#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* command;
    char* args;
} Command;

void restore_command(const char* input_file) {
    Command* cmd = (Command*)input_file;
    printf("Command: %s, Args: %s\n", cmd->command, cmd->args);
}

int main() {
    const char* input_file = "{\"command\":\"restore\",\"args\":\"--all\"}";
    restore_command(input_file);
    return 0;
}