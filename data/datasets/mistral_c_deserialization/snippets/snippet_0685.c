#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#define MAX_FILE_SIZE 1024

typedef struct {
    char filename[50];
    int size;
} FileState;

int validate_file_state(json_object *jobj) {
    json_object *jfilename, *jsize;

    if (!json_object_object_get_ex(jobj, "filename", &jfilename) ||
        !json_object_object_get_ex(jobj, "size", &jsize)) {
        return 0;
    }

    if (json_object_get_type(jfilename) != json_type_string ||
        json_object_get_type(jsize) != json_type_int) {
        return 0;
    }

    return 1;
}

FileState* import_file_state(const char *file_content) {
    json_object *jobj = json_tokener_parse(file_content);
    if (jobj == NULL) {
        return NULL;
    }

    if (!validate_file_state(jobj)) {
        json_object_put(jobj);
        return NULL;
    }

    FileState *state = (FileState*)malloc(sizeof(FileState));
    if (state == NULL) {
        json_object_put(jobj);
        return NULL;
    }

    strcpy(state->filename, json_object_get_string(json_object_object_get(jobj, "filename")));
    state->size = json_object_get_int(json_object_object_get(jobj, "size"));

    json_object_put(jobj);
    return state;
}

int main() {
    char file_content[MAX_FILE_SIZE];
    printf("Enter file content: ");
    fgets(file_content, MAX_FILE_SIZE, stdin);

    FileState *state = import_file_state(file_content);
    if (state != NULL) {
        printf("Filename: %s\nSize: %d\n", state->filename, state->size);
        free(state);
    } else {
        printf("Invalid file content.\n");
    }

    return 0;
}