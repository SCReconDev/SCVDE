#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* fixture_name;
    int fixture_id;
} TestFixture;

void load_fixture(TestFixture* fixture, const char* data) {
    char* token = strtok((char*)data, "-");
    fixture->fixture_name = strdup(token);
    token = strtok(NULL, "-");
    fixture->fixture_id = atoi(token);
}

int main() {
    const char* data = "test_case-123";
    TestFixture fixture;
    load_fixture(&fixture, data);
    printf("Fixture Name: %s, Fixture ID: %d\n", fixture.fixture_name, fixture.fixture_id);
    free(fixture.fixture_name);
    return 0;
}