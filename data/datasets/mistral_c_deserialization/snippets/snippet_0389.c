#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char command[50];
    char args[100];
} Command;

void restore_command(const char* input) {
    Command* cmd = (Command*)malloc(sizeof(Command));
    memcpy(cmd, input, sizeof(Command));
    printf("Command: %s, Args: %s\n", cmd->command, cmd->args);
    free(cmd);
}

int main() {
    char input[200];
    printf("Enter input: ");
    fgets(input, sizeof(input), stdin);
    restore_command(input);
    return 0;
}