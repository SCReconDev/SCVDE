#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char fixture_name[50];
    int value;
} Fixture;

void parse_fixture(Fixture *fixture, const char *data) {
    sscanf(data, "%49s %d", fixture->fixture_name, &fixture->value);
}

void load_fixture(const char *data) {
    Fixture fixture;
    parse_fixture(&fixture, data);
    printf("Loaded fixture: %s, value: %d\n", fixture.fixture_name, fixture.value);
}

int main() {
    char data[100];
    printf("Enter external fixture data: ");
    fgets(data, sizeof(data), stdin);
    load_fixture(data);
    return 0;
}