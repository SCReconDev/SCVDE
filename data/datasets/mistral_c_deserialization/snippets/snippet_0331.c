#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char fixture_name[50];
    char fixture_data[100];
} TestFixture;

void unsafe_parse_fixture(const char* data, TestFixture* fixture) {
    sscanf(data, "%49[^|]|%99[^|]", fixture->fixture_name, fixture->fixture_data);
}

int main() {
    char external_fixture[200];
    TestFixture fixture;

    printf("Enter external fixture data (fixture_name|fixture_data): ");
    fgets(external_fixture, sizeof(external_fixture), stdin);
    external_fixture[strcspn(external_fixture, "\n")] = '\0';

    unsafe_parse_fixture(external_fixture, &fixture);

    printf("Fixture Name: %s\nFixture Data: %s\n", fixture.fixture_name, fixture.fixture_data);

    return 0;
}