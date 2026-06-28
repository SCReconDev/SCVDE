#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int value;
} Fixture;

void parse_fixture(Fixture* fixture, const char* data) {
    char* token = strtok((char*)data, " ");
    fixture->name = strdup(token);
    token = strtok(NULL, " ");
    fixture->value = atoi(token);
}

void load_fixture(const char* data) {
    Fixture fixture;
    parse_fixture(&fixture, data);
    printf("Name: %s, Value: %d\n", fixture.name, fixture.value);
    free(fixture.name);
}

int main() {
    const char* data = "test 1";
    load_fixture(data);
    return 0;
}