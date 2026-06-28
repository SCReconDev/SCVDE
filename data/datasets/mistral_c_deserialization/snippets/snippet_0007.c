#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char command[50];
    int param;
} Command;

void load_command(Command *command, const char *file_content) {
    sscanf(file_content, "%49s %d", command->command, &command->param);
}

void restore_command(const char *file_content) {
    Command command;
    load_command(&command, file_content);
    printf("Command: %s, Param: %d\n", command.command, command.param);
}

int main() {
    char file_content[100];
    printf("Enter file content: ");
    fgets(file_content, sizeof(file_content), stdin);
    restore_command(file_content);
    return 0;
}