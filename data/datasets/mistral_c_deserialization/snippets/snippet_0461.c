#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char fixture_name[50];
    int fixture_value;
} TestFixture;

void deserialize_fixture(char* data, TestFixture* fixture) {
    char* token = strtok(data, ",");
    strcpy(fixture->fixture_name, token);
    token = strtok(NULL, ",");
    fixture->fixture_value = atoi(token);
}

void load_fixture(char* external_fixture) {
    TestFixture fixture;
    deserialize_fixture(external_fixture, &fixture);
    printf("Loaded fixture: %s, value %d\n", fixture.fixture_name, fixture.fixture_value);
}

int main() {
    char external_fixture[] = "test_data,100";
    load_fixture(external_fixture);
    return 0;
}