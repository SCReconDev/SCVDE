#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* filename;
    char* content;
} FileData;

void deserialize_file_data(const char* state, FileData* data) {
    char* token = strtok((char*)state, ";");
    data->filename = strdup(token);

    token = strtok(NULL, ";");
    data->content = strdup(token);
}

int main() {
    const char* state = "test.txt;Hello, World!";
    FileData data;

    deserialize_file_data(state, &data);

    printf("Filename: %s, Content: %s\n", data.filename, data.content);

    free(data.filename);
    free(data.content);
    return 0;
}