#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char fixture_name[50];
    char fixture_data[255];
} Fixture;

bool validate_fixture(Fixture* fixture) {
    if (strlen(fixture->fixture_name) == 0 || strlen(fixture->fixture_name) >= 50) {
        return false;
    }
    if (strlen(fixture->fixture_data) >= 255) {
        return false;
    }
    return true;
}

void process_fixture(Fixture* fixture) {
    if (validate_fixture(fixture)) {
        printf("Fixture Name: %s, Data: %s\n", fixture->fixture_name, fixture->fixture_data);
    } else {
        printf("Invalid fixture data\n");
    }
}

int main() {
    Fixture fixture1 = {"example_fixture", "{\"setting1\": \"value1\", \"setting2\": \"value2\"}"};
    Fixture fixture2 = {"", "{\"invalid\": \"data\"}"};

    process_fixture(&fixture1);
    process_fixture(&fixture2);

    return 0;
}