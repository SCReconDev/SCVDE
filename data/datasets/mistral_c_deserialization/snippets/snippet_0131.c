#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIXTURE_SIZE 1024

void load_fixture(const char *fixture_path) {
    FILE *file = fopen(fixture_path, "r");
    if (file == NULL) {
        perror("fopen");
        return;
    }

    char *fixture_data = (char *)malloc(FIXTURE_SIZE);
    if (fixture_data == NULL) {
        fclose(file);
        return;
    }

    size_t bytes_read = fread(fixture_data, 1, FIXTURE_SIZE - 1, file);
    if (bytes_read == 0) {
        free(fixture_data);
        fclose(file);
        return;
    }
    fixture_data[bytes_read] = '\0';

    void *fixture = deserialize_fixture(fixture_data, bytes_read);
    if (fixture == NULL) {
        free(fixture_data);
        fclose(file);
        return;
    }

    printf("Fixture loaded successfully.\n");

    free(fixture);
    free(fixture_data);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <fixture_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    load_fixture(argv[1]);

    return 0;
}