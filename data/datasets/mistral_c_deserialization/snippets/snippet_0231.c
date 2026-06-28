#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char fixture_name[50];
    char fixture_data[100];
} TestFixture;

void load_fixture(const char* external, TestFixture* fixture) {
    char* data = strdup(external);
    char* token = strtok(data, "=");
    strcpy(fixture->fixture_name, token);
    token = strtok(NULL, "=");
    strcpy(fixture->fixture_data, token);
    free(data);
}

int main() {
    char* external = "user_data=name:John,age:30";
    TestFixture fixture;
    load_fixture(external, &fixture);
    printf("Fixture Name: %s, Fixture Data: %s\n", fixture.fixture_name, fixture.fixture_data);
    return 0;
}