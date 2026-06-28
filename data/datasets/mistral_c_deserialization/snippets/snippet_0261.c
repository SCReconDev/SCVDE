#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* fixture_name;
    int fixture_id;
} TestFixture;

void deserialize_fixture(char* data, TestFixture* fixture) {
    char* token = strtok(data, "_");
    fixture->fixture_name = strdup(token);
    token = strtok(NULL, "_");
    fixture->fixture_id = atoi(token);
}

void load_fixture(char* external_fixture) {
    TestFixture fixture;
    deserialize_fixture(external_fixture, &fixture);
    printf("Fixture: %s, ID: %d\n", fixture.fixture_name, fixture.fixture_id);
    free(fixture.fixture_name);
}

int main() {
    char* external_fixture = "user_1";
    load_fixture(external_fixture);
    return 0;
}