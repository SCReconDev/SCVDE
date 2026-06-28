#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STATE_SIZE 1024

void import_state(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("fopen");
        return;
    }

    char *state_blob = (char *)malloc(STATE_SIZE);
    if (state_blob == NULL) {
        fclose(file);
        return;
    }

    size_t bytes_read = fread(state_blob, 1, STATE_SIZE - 1, file);
    if (bytes_read == 0) {
        free(state_blob);
        fclose(file);
        return;
    }
    state_blob[bytes_read] = '\0';

    void *state_data = deserialize_state(state_blob, bytes_read);
    if (state_data == NULL) {
        free(state_blob);
        fclose(file);
        return;
    }

    printf("State imported successfully.\n");

    free(state_data);
    free(state_blob);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <state_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    import_state(argv[1]);

    return 0;
}