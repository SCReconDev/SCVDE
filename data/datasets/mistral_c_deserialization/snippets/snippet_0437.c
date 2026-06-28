#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    char* state;
} FileImport;

void import_file(FileImport* file) {
    printf("Importing file: %s, State: %s\n", file->name, file->state);
}

int main() {
    char* uploaded_state = "{\"name\":\"data.csv\",\"state\":\"pending\"}";
    FileImport* file = (FileImport*)malloc(sizeof(FileImport));
    memcpy(file, uploaded_state, sizeof(FileImport));
    import_file(file);
    free(file);
    return 0;
}