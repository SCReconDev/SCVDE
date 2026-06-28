#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* fixture_name;
    char* fixture_data;
} Fixture;

void load_fixture(Fixture* fixture) {
    printf("Fixture Name: %s\n", fixture->fixture_name);
    printf("Fixture Data: %s\n", fixture->fixture_data);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <external_fixture>\n", argv[0]);
        return 1;
    }

    char* external_fixture = argv[1];
    Fixture* fixture = (Fixture*)external_fixture;
    load_fixture(fixture);

    return 0;
}