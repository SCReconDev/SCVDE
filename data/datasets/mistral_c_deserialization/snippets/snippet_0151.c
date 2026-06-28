#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char fixture_name[50];
    char fixture_data[200];
} FixtureData;

void deserialize_fixture_data(FixtureData *fixture_data, const char *data) {
    memcpy(fixture_data, data, sizeof(FixtureData));
}

void load_fixture(const char *external_fixture) {
    FixtureData fixture_data;
    deserialize_fixture_data(&fixture_data, external_fixture);
    printf("Loaded fixture: %s\n", fixture_data.fixture_name);
}

int main() {
    char external_fixture[250];
    printf("Enter external fixture: ");
    fgets(external_fixture, sizeof(external_fixture), stdin);
    external_fixture[strcspn(external_fixture, "\n")] = '\0';

    load_fixture(external_fixture);
    return 0;
}