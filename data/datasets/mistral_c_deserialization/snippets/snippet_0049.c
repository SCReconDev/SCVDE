#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* fixture_name;
    int test_count;
} TestFixture;

void process_test_fixture(TestFixture* fixture) {
    printf("Fixture Name: %s\n", fixture->fixture_name);
    printf("Test Count: %d\n", fixture->test_count);
}

void deserialize_test_fixture(const char* fixture, TestFixture* fixture_struct) {
    char* data = strdup(fixture);
    char* token = strtok(data, "-");
    fixture_struct->fixture_name = strdup(token);
    token = strtok(NULL, "-");
    fixture_struct->test_count = atoi(token);
    free(data);
}

void load_test_fixture(const char* fixture) {
    TestFixture fixture_struct;
    deserialize_test_fixture(fixture, &fixture_struct);
    process_test_fixture(&fixture_struct);
}

int main() {
    const char* fixture = "DatabaseOperations-10";
    load_test_fixture(fixture);
    return 0;
}