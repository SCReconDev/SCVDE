#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* fixture_name;
    int value;
} TestFixture;

void load_fixture(const char* fixture, TestFixture* test) {
    char* token = strtok((char*)fixture, "-");
    test->fixture_name = strdup(token);
    token = strtok(NULL, "-");
    test->value = atoi(token);
}

int main() {
    char* fixture = "test_value-42";
    TestFixture test;
    load_fixture(fixture, &test);
    printf("Fixture Name: %s, Value: %d\n", test.fixture_name, test.value);
    free(test.fixture_name);
    return 0;
}