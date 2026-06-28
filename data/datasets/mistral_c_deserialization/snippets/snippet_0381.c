#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* fixture_name;
    int value;
} Fixture;

void load_fixture(const char* fixture) {
    Fixture fix;
    char* decoded = strdup(fixture);
    char* token = strtok(decoded, ",");
    fix.fixture_name = strdup(token);
    token = strtok(NULL, ",");
    fix.value = atoi(token);
    printf("Fixture loaded: %s = %d\n", fix.fixture_name, fix.value);
    free(fix.fixture_name);
    free(decoded);
}

int main() {
    const char* fixture = "test_value,42";
    load_fixture(fixture);
    return 0;
}