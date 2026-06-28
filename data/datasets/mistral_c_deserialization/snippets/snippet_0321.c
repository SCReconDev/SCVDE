#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* fixture_name;
    int test_count;
    char* results;
} TestFixture;

void load_fixture(const char* data, TestFixture* fixture) {
    char* token = strtok((char*)data, "/");
    fixture->fixture_name = strdup(token);
    token = strtok(NULL, "/");
    fixture->test_count = atoi(token);
    token = strtok(NULL, "/");
    fixture->results = strdup(token);
}

int main() {
    char* fixture_data = "network_tests/10/{passed: 8, failed: 2}";
    TestFixture fixture;
    load_fixture(fixture_data, &fixture);
    printf("Fixture Name: %s, Test Count: %d, Results: %s\n", fixture.fixture_name, fixture.test_count, fixture.results);
    free(fixture.fixture_name);
    free(fixture.results);
    return 0;
}