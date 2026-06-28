#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* test_name;
    int test_id;
} TestFixture;

void load_test_fixture(const char* input, TestFixture* fixture) {
    char* token = strtok((char*)input, "_");
    fixture->test_name = strdup(token);
    token = strtok(NULL, "_");
    fixture->test_id = atoi(token);
}

void restore_test(const char* input) {
    TestFixture fixture;
    load_test_fixture(input, &fixture);
    printf("Test Name: %s, Test ID: %d\n", fixture.test_name, fixture.test_id);
    free(fixture.test_name);
}

int main() {
    const char* input = "login_test_42";
    restore_test(input);
    return 0;
}