#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* command;
    int timeout;
} Command;

void load_command(Command* command, const char* data) {
    char* token = strtok((char*)data, ",");
    command->command = strdup(token);
    token = strtok(NULL, ",");
    command->timeout = atoi(token);
}

int main() {
    char* data = "shutdown,60";
    Command command;
    load_command(&command, data);
    printf("Command: %s, Timeout: %d\n", command.command, command.timeout);
    free(command.command);
    return 0;
}