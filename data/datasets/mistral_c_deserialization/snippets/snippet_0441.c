#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* fixture_name;
    char* fixture_data;
} TestFixture;

void load_fixture(TestFixture* fixture) {
    printf("Loading fixture: %s, Data: %s\n", fixture->fixture_name, fixture->fixture_data);
}

int main() {
    char* external_fixture = "{\"fixture_name\":\"user\",\"fixture_data\":\"admin\"}";
    TestFixture* fixture = (TestFixture*)malloc(sizeof(TestFixture));
    memcpy(fixture, external_fixture, sizeof(TestFixture));
    load_fixture(fixture);
    free(fixture);
    return 0;
}