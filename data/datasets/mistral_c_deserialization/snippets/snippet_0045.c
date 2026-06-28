#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* filename;
    int file_size;
} FileInfo;

void process_file_info(FileInfo* info) {
    printf("Filename: %s\n", info->filename);
    printf("File Size: %d\n", info->file_size);
}

void deserialize_file_info(const char* state, FileInfo* info) {
    char* data = strdup(state);
    char* token = strtok(data, "|");
    info->filename = strdup(token);
    token = strtok(NULL, "|");
    info->file_size = atoi(token);
    free(data);
}

void import_file(const char* state) {
    FileInfo info;
    deserialize_file_info(state, &info);
    process_file_info(&info);
}

int main() {
    const char* state = "document.txt|1024";
    import_file(state);
    return 0;
}