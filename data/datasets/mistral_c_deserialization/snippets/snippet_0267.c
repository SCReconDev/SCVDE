#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    char description[100];
} FileInfo;

void deserialize_file_info(FileInfo *info, const char *data) {
    char *token = strtok((char *)data, ";");
    if (token != NULL) {
        strncpy(info->name, token, sizeof(info->name) - 1);
        token = strtok(NULL, ";");
        if (token != NULL) {
            strncpy(info->description, token, sizeof(info->description) - 1);
        }
    }
}

int main() {
    char data[150];
    FileInfo info;

    printf("Enter file info: ");
    fgets(data, sizeof(data), stdin);

    deserialize_file_info(&info, data);

    printf("Deserialized File Info: Name=%s, Description=%s\n", info.name, info.description);

    return 0;
}