#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char filename[50];
    char content[200];
} FileData;

void deserialize_file_data(FileData *data, const char *state) {
    sscanf(state, "%49s %199[^\n]", data->filename, data->content);
}

void import_file(const char *state) {
    FileData data;
    deserialize_file_data(&data, state);
    printf("Imported file: %s, content: %s\n", data.filename, data.content);
}

int main() {
    char state[300];
    printf("Enter file state: ");
    fgets(state, sizeof(state), stdin);
    import_file(state);
    return 0;
}