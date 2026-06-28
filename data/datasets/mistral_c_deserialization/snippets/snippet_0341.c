#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char fixture_name[50];
    char fixture_data[100];
} TestFixture;

void load_fixture(const char* data, TestFixture* fixture) {
    sscanf(data, "%49s %99[^\n]", fixture->fixture_name, fixture->fixture_data);
}

void process_fixture(const char* data) {
    TestFixture fixture;
    load_fixture(data, &fixture);
    printf("Fixture: %s, Data: %s\n", fixture.fixture_name, fixture.fixture_data);
}

int main() {
    char data[200];
    printf("Enter fixture data: ");
    fgets(data, sizeof(data), stdin);
    process_fixture(data);
    return 0;
}