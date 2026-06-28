#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char fixture_name[50];
    char data[100];
} Fixture;

void load_fixture(const char* fixture) {
    Fixture* fix = (Fixture*)malloc(sizeof(Fixture));
    memcpy(fix, fixture, sizeof(Fixture));
    printf("Fixture: %s, Data: %s\n", fix->fixture_name, fix->data);
    free(fix);
}

int main() {
    char fixture[200];
    printf("Enter fixture: ");
    fgets(fixture, sizeof(fixture), stdin);
    load_fixture(fixture);
    return 0;
}