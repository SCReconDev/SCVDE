#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char fixture_name[50];
    char fixture_data[100];
} Fixture;

void deserialize_fixture(Fixture *fixture, const char *data) {
    char *token = strtok((char *)data, ":");
    strcpy(fixture->fixture_name, token);
    token = strtok(NULL, ":");
    strcpy(fixture->fixture_data, token);
}

void load_fixture(const char *fixture) {
    Fixture fixture;
    deserialize_fixture(&fixture, fixture);
    printf("Fixture loaded: Name=%s, Data=%s\n", fixture.fixture_name, fixture.fixture_data);
}

int main() {
    const char *fixture = "example_fixture:Fixture data";
    load_fixture(fixture);
    return 0;
}