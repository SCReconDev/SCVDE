#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char command_name[50];
    char command_args[200];
} Command;

bool validate_command(Command* command) {
    if (strlen(command->command_name) == 0 || strlen(command->command_args) == 0) {
        return false;
    }
    return true;
}

void execute_command(Command* command) {
    if (validate_command(command)) {
        printf("Command executed: %s, %s\n", command->command_name, command->command_args);
    } else {
        printf("Invalid command data\n");
    }
}

int main() {
    Command command1 = {"restore", "--source /path/to/source --destination /path/to/destination"};
    Command command2 = {"", "--source /path/to/source --destination /path/to/destination"};

    execute_command(&command1);
    execute_command(&command2);

    return 0;
}