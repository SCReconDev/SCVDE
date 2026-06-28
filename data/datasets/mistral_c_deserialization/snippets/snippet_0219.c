#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char command[50];
    int param;
} Command;

void restore_data(char* input_file) {
    Command* cmd = (Command*)malloc(sizeof(Command));
    memcpy(cmd, input_file, sizeof(Command));
    printf("Command restored: %s (Param: %d)\n", cmd->command, cmd->param);
    free(cmd);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    char* input_file = argv[1];
    restore_data(input_file);

    return 0;
}