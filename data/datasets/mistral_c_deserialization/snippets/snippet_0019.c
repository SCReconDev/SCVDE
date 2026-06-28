#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* fixture_name;
    int value;
} TestFixture;

void deserialize_test_fixture(TestFixture* fixture, const char* data) {
    char* token = strtok((char*)data, "=");
    fixture->fixture_name = strdup(token);
    token = strtok(NULL, "=");
    fixture->value = atoi(token);
}

void load_test_fixture(const char* external_fixture) {
    TestFixture fixture;
    deserialize_test_fixture(&fixture, external_fixture);
    printf("Test Fixture - Name: %s, Value: %d\n", fixture.fixture_name, fixture.value);
    free(fixture.fixture_name);
}

int main() {
    const char* external_fixture = "test_case=100";
    load_test_fixture(external_fixture);
    return 0;
}