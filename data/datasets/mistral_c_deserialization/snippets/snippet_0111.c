#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* fixture_name;
    int version;
} TestFixture;

void load_fixture(TestFixture* fixture, const char* data) {
    char* token = strdup(data);
    char* part = strtok(token, "|");
    fixture->fixture_name = strdup(part);
    part = strtok(NULL, "|");
    fixture->version = atoi(part);
    free(token);
}

int main() {
    char* data = "fixture1|2";
    TestFixture fixture;
    load_fixture(&fixture, data);
    printf("Fixture Name: %s, Version: %d\n", fixture.fixture_name, fixture.version);
    return 0;
}