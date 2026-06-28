#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* fixture_name;
    char* fixture_data;
} TestFixture;

void load_fixture(TestFixture* fixture, const char* data) {
    char* token = strtok((char*)data, ":");
    fixture->fixture_name = strdup(token);
    token = strtok(NULL, ":");
    fixture->fixture_data = strdup(token);
}

int main() {
    char* fixture_data = "test_data:sample data for testing";
    TestFixture fixture;
    load_fixture(&fixture, fixture_data);
    printf("Fixture Name: %s, Fixture Data: %s\n", fixture.fixture_name, fixture.fixture_data);
    free(fixture.fixture_name);
    free(fixture.fixture_data);
    return 0;
}