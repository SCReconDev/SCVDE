#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* filename;
    char* content;
} FileData;

void deserialize_file_data(const char* state, FileData* file_data) {
    char* token = strtok((char*)state, "::");
    file_data->filename = strdup(token);
    token = strtok(NULL, "::");
    file_data->content = strdup(token);
}

void import_file(const char* state) {
    FileData file_data;
    deserialize_file_data(state, &file_data);
    printf("Filename: %s, Content: %s\n", file_data.filename, file_data.content);
    free(file_data.filename);
    free(file_data.content);
}

int main() {
    const char* state = "report.txt::This is a sample report.";
    import_file(state);
    return 0;
}