#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char fixture_name[50];
    char data[100];
} Fixture;

void load_fixture(const char* data, Fixture* fixture) {
    sscanf(data, "%49s %99[^\n]", fixture->fixture_name, fixture->data);
}

int main() {
    char external_fixture[200];
    Fixture fixture;

    printf("Enter external fixture data (fixture_name data): ");
    fgets(external_fixture, sizeof(external_fixture), stdin);

    load_fixture(external_fixture, &fixture);

    printf("Loaded Fixture: Fixture Name=%s, Data=%s\n", fixture.fixture_name, fixture.data);

    return 0;
}