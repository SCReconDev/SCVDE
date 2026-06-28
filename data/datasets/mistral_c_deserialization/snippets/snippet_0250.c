#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* fixture_name;
    char* fixture_data;
} Fixture;

Fixture* load_fixture(const char* fixture) {
    Fixture* fix = malloc(sizeof(Fixture));
    char* token = strtok((char*)fixture, "-");
    fix->fixture_name = strdup(token);
    token = strtok(NULL, "-");
    fix->fixture_data = strdup(token);
    return fix;
}

void use_fixture(const char* fixture) {
    Fixture* fix = load_fixture(fixture);
    printf("Fixture: %s\n", fix->fixture_name);
    free(fix->fixture_name);
    free(fix->fixture_data);
    free(fix);
}

int main() {
    char* fixture = "user-admin";
    use_fixture(fixture);
    return 0;
}