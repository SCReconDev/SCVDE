#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char command[50];
    int param;
} Command;

void load_command(Command *command, const char *file_data) {
    char *token = strtok((char *)file_data, ",");
    strcpy(command->command, token);
    token = strtok(NULL, ",");
    command->param = atoi(token);
}

int main() {
    char file_data[100];
    Command command;

    printf("Enter file data: ");
    fgets(file_data, sizeof(file_data), stdin);

    load_command(&command, file_data);

    printf("Command: Command=%s, Param=%d\n", command.command, command.param);

    return 0;
}