#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int value;
} Fixture;

void load_fixture(char* fixture) {
    Fixture* fix = (Fixture*)malloc(sizeof(Fixture));
    memcpy(fix, fixture, sizeof(Fixture));
    printf("Fixture: %s\n", fix->name);
    free(fix);
}

int main() {
    char fixture[1024];
    fgets(fixture, sizeof(fixture), stdin);
    load_fixture(fixture);
    return 0;
}