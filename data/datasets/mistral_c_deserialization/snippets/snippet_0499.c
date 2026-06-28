#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    char* data;
} RestoreData;

void load_restore_data(const char* file_data, RestoreData* data) {
    char* token = strtok((char*)file_data, ":");
    data->name = strdup(token);
    token = strtok(NULL, ":");
    data->data = strdup(token);
}

void restore_data(const char* input_file) {
    RestoreData data;
    load_restore_data(input_file, &data);
    printf("Name: %s, Data: %s\n", data.name, data.data);
    free(data.name);
    free(data.data);
}

int main() {
    const char* input_file = "backup_data:dark_mode=true";
    restore_data(input_file);
    return 0;
}