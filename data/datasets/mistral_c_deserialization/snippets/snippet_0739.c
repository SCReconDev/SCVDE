#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char fixture_name[50];
    char fixture_data[200];
} Fixture;

bool validate_fixture(Fixture* fixture) {
    if (strlen(fixture->fixture_name) == 0 || strlen(fixture->fixture_data) == 0) {
        return false;
    }
    return true;
}

void load_fixture(Fixture* fixture) {
    if (validate_fixture(fixture)) {
        printf("Fixture loaded: %s, %s\n", fixture->fixture_name, fixture->fixture_data);
    } else {
        printf("Invalid fixture data\n");
    }
}

int main() {
    Fixture fixture1 = {"example_fixture", "{\"param1\": \"value1\", \"param2\": \"value2\"}"};
    Fixture fixture2 = {"", "{\"param1\": \"value1\", \"param2\": \"value2\"}"};

    load_fixture(&fixture1);
    load_fixture(&fixture2);

    return 0;
}