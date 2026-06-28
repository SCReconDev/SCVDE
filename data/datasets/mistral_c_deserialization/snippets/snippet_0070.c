#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* fixture_name;
    char* fixture_data;
} TestFixture;

void parse_fixture(const char* fixture, TestFixture* test_fixture) {
    char* token = strtok((char*)fixture, ":");
    test_fixture->fixture_name = strdup(token);
    token = strtok(NULL, ":");
    test_fixture->fixture_data = strdup(token);
}

void load_test_fixture(const char* fixture) {
    TestFixture test_fixture;
    parse_fixture(fixture, &test_fixture);
    printf("Fixture Name: %s, Fixture Data: %s\n", test_fixture.fixture_name, test_fixture.fixture_data);
    free(test_fixture.fixture_name);
    free(test_fixture.fixture_data);
}

int main() {
    const char* fixture = "user_data:John Doe,30";
    load_test_fixture(fixture);
    return 0;
}