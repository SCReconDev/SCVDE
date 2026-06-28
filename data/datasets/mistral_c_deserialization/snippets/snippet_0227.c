#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    char description[100];
} FileInfo;

void import_file(const char* state, FileInfo* info) {
    char* data = strdup(state);
    char* token = strtok(data, ",");
    strcpy(info->name, token);
    token = strtok(NULL, ",");
    strcpy(info->description, token);
    free(data);
}

int main() {
    char* state = "document.txt,This is a test document";
    FileInfo info;
    import_file(state, &info);
    printf("Name: %s, Description: %s\n", info.name, info.description);
    return 0;
}