#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char dataset[50];
    char parameters[100];
} RestoreCommand;

void parse_restore_command(const char* input, RestoreCommand* cmd) {
    char* data = strdup(input);
    char* token = strtok(data, " ");
    strcpy(cmd->dataset, token);
    token = strtok(NULL, " ");
    strcpy(cmd->parameters, token);
    free(data);
}

int main() {
    char* input = "sales_data --verbose";
    RestoreCommand cmd;
    parse_restore_command(input, &cmd);
    printf("Dataset: %s, Parameters: %s\n", cmd.dataset, cmd.parameters);
    return 0;
}