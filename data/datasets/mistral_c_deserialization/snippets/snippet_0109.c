#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char* data;
} RestoreData;

void restore_data(RestoreData* data, const char* file_content) {
    char* token = strdup(file_content);
    char* part = strtok(token, "|");
    data->id = atoi(part);
    part = strtok(NULL, "|");
    data->data = strdup(part);
    free(token);
}

int main() {
    char* file_content = "789|Restored data";
    RestoreData data;
    restore_data(&data, file_content);
    printf("ID: %d, Data: %s\n", data.id, data.data);
    return 0;
}