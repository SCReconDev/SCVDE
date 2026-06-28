#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST_CONFIG_FILE "test_config.txt"

void read_config(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

int main(void) {
    char *test_credential = getenv("TEST_CREDENTIAL");
    if (!test_credential) {
        fprintf(stderr, "TEST_CREDENTIAL environment variable not set\n");
        return 1;
    }

    printf("Test credential: %s\n", test_credential);

    read_config(TEST_CONFIG_FILE);

    return 0;
}