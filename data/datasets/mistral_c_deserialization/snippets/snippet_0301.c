#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* fixture_name;
    int value;
} Fixture;

void load_fixture(const char* external) {
    Fixture* fixture = (Fixture*)malloc(sizeof(Fixture));
    memcpy(fixture, external, sizeof(Fixture));

    printf("Fixture: %s, Value: %d\n", fixture->fixture_name, fixture->value);
    free(fixture);
}

int main() {
    char* external_fixture = "sensor_data\0100";
    load_fixture(external_fixture);
    return 0;
}