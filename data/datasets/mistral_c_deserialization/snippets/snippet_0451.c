#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char fixture_name[50];
    char fixture_data[100];
} Fixture;

void load_fixture(const char* fixture) {
    Fixture* fix = (Fixture*)malloc(sizeof(Fixture));
    memcpy(fix, fixture, sizeof(Fixture));
    printf("Fixture Name: %s, Fixture Data: %s\n", fix->fixture_name, fix->fixture_data);
    free(fix);
}

int main() {
    char fixture[sizeof(Fixture)];
    memset(fixture, 0, sizeof(fixture));
    strcpy(fixture, "example_fixture");
    strcpy(fixture + 50, "example_fixture_data");

    load_fixture(fixture);
    return 0;
}