#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* fixture_name;
    int fixture_id;
} Fixture;

void load_fixture(const char* data, Fixture* fixture) {
    char* token = strtok((char*)data, "_");
    fixture->fixture_name = strdup(token);
    token = strtok(NULL, "_");
    fixture->fixture_id = atoi(token);
}

int main() {
    char fixture_data[] = "fixture1_123";
    Fixture fixture;
    load_fixture(fixture_data, &fixture);

    printf("Fixture Name: %s, ID: %d\n", fixture.fixture_name, fixture.fixture_id);
    free(fixture.fixture_name);

    return 0;
}