#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* fixture_name;
    int value;
} Fixture;

void load_fixture(const char* data, Fixture* fixture) {
    char* token = strtok((char*)data, ":");
    fixture->fixture_name = strdup(token);
    token = strtok(NULL, ":");
    fixture->value = atoi(token);
}

int main() {
    char* fixture_data = "test_fixture:10";
    Fixture fixture;
    load_fixture(fixture_data, &fixture);
    printf("Fixture Name: %s, Value: %d\n", fixture.fixture_name, fixture.value);
    free(fixture.fixture_name);
    return 0;
}