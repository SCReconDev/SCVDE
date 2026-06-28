#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* fixture_name;
    int value;
} Fixture;

void load_fixture(const char* fixture_data, Fixture* fixture) {
    char* data = strdup(fixture_data);
    char* token = strtok(data, ":");
    fixture->fixture_name = strdup(token);
    token = strtok(NULL, ":");
    fixture->value = atoi(token);
    free(data);
}

int main() {
    char* fixture_data = "test_fixture:100";
    Fixture fixture;
    load_fixture(fixture_data, &fixture);
    printf("Fixture Name: %s, Value: %d\n", fixture.fixture_name, fixture.value);
    free(fixture.fixture_name);
    return 0;
}