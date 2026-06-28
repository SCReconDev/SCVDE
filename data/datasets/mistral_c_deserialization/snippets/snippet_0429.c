#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    char data[100];
} RestoreData;

void deserialize_restore_data(RestoreData *data, const char *input) {
    char *token = strtok((char *)input, ",");
    strcpy(data->name, token);
    token = strtok(NULL, ",");
    strcpy(data->data, token);
}

void restore_data(const char *file) {
    RestoreData data;
    deserialize_restore_data(&data, file);
    printf("Data restored: Name=%s, Data=%s\n", data.name, data.data);
}

int main() {
    const char *file = "backup.txt,Backup data";
    restore_data(file);
    return 0;
}