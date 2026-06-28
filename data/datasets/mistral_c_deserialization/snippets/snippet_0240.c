#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    char* value;
} Fixture;

void parse_fixture(Fixture* fixture, const char* data) {
    char* token = strtok((char*)data, "-");
    fixture->name = strdup(token);
    token = strtok(NULL, "-");
    fixture->value = strdup(token);
}

int main() {
    FILE* file = fopen("fixture_data.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        perror("Error reading file");
        fclose(file);
        return 1;
    }

    Fixture fixture;
    parse_fixture(&fixture, buffer);

    printf("Name: %s, Value: %s\n", fixture.name, fixture.value);

    free(fixture.name);
    free(fixture.value);
    fclose(file);
    return 0;
}