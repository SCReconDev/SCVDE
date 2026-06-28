#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* fixture_name;
    char* fixture_data;
} Fixture;

void load_fixture(const char* external_fixture) {
    Fixture* fixture = (Fixture*)external_fixture;
    printf("Fixture Name: %s, Fixture Data: %s\n", fixture->fixture_name, fixture->fixture_data);
}

int main() {
    const char* external_fixture = "{\"fixture_name\":\"test_data\",\"fixture_data\":\"sample_data\"}";
    load_fixture(external_fixture);
    return 0;
}