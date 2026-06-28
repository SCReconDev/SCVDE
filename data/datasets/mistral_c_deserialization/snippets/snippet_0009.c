#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char fixture_name[50];
    int fixture_value;
} Fixture;

void parse_fixture(Fixture *fixture, const char *external_data) {
    sscanf(external_data, "%49s %d", fixture->fixture_name, &fixture->fixture_value);
}

void load_fixture(const char *external_data) {
    Fixture fixture;
    parse_fixture(&fixture, external_data);
    printf("Fixture Name: %s, Fixture Value: %d\n", fixture.fixture_name, fixture.fixture_value);
}

int main() {
    char external_data[100];
    printf("Enter external data: ");
    fgets(external_data, sizeof(external_data), stdin);
    load_fixture(external_data);
    return 0;
}