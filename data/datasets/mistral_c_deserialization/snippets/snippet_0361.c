#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char fixture_name[50];
    int value;
} Fixture;

void parse_fixture(const char* data, Fixture* fixture) {
    char* decoded_data = malloc(strlen(data) + 1);
    strcpy(decoded_data, data);
    sscanf(decoded_data, "%49s %d", fixture->fixture_name, &fixture->value);
    free(decoded_data);
}

void load_test_fixture(const char* fixture_data) {
    Fixture fixture;
    parse_fixture(fixture_data, &fixture);
    printf("Fixture: %s, Value: %d\n", fixture.fixture_name, fixture.value);
}

int main() {
    const char* fixture_data = "test_data 100";
    load_test_fixture(fixture_data);
    return 0;
}