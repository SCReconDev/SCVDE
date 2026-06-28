#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[256];
    int value;
} Fixture;

void deserialize_fixture(Fixture *fixture, const char *data) {
    sscanf(data, "%255[^;];%d", fixture->name, &fixture->value);
}

void load_fixture(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    char buffer[512];
    fgets(buffer, sizeof(buffer), file);
    fclose(file);
    Fixture fixture;
    deserialize_fixture(&fixture, buffer);
    printf("Fixture: %s = %d\n", fixture.name, fixture.value);
}

int main() {
    char file_path[256];
    printf("Enter file path: ");
    fgets(file_path, sizeof(file_path), stdin);
    file_path[strcspn(file_path, "\n")] = 0;
    load_fixture(file_path);
    return 0;
}