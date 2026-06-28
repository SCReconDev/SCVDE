#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    char* data;
} Fixture;

void load_fixture(Fixture* fixture, const char* external) {
    char* token = strtok((char*)external, ",");
    fixture->name = strdup(token);
    token = strtok(NULL, ",");
    fixture->data = strdup(token);
}

int main() {
    char external[100];
    printf("Enter external fixture: ");
    fgets(external, sizeof(external), stdin);
    external[strcspn(external, "\n")] = 0;

    Fixture fixture;
    load_fixture(&fixture, external);

    printf("Name: %s, Data: %s\n", fixture.name, fixture.data);
    free(fixture.name);
    free(fixture.data);
    return 0;
}