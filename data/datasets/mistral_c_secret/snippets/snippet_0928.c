#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY_FILE "private_key.pem"

void read_private_key(const char *filename) {
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
    char *admin_password = getenv("ADMIN_PASSWORD");
    if (!admin_password) {
        fprintf(stderr, "ADMIN_PASSWORD environment variable not set\n");
        return 1;
    }

    printf("Admin password: %s\n", admin_password);

    read_private_key(PRIVATE_KEY_FILE);

    return 0;
}