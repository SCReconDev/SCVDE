#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char command_name[50];
    char command_args[255];
} Command;

bool validate_command(Command* command) {
    if (strlen(command->command_name) == 0 || strlen(command->command_name) >= 50) {
        return false;
    }
    if (strlen(command->command_args) >= 255) {
        return false;
    }
    return true;
}

void process_command(Command* command) {
    if (validate_command(command)) {
        printf("Command Name: %s, Args: %s\n", command->command_name, command->command_args);
    } else {
        printf("Invalid command data\n");
    }
}

int main() {
    Command command1 = {"backup", "--all --verbose"};
    Command command2 = {"", "--invalid"};

    process_command(&command1);
    process_command(&command2);

    return 0;
}