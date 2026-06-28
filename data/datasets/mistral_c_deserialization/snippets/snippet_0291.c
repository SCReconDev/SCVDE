#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    char fixture[100];
} TestFixture;

void load_fixture(TestFixture *fixture, const char *data) {
    sscanf(data, "%49s %99[^\n]", fixture->name, fixture->fixture);
}

void load_test_fixture(const char *data) {
    TestFixture fixture;
    load_fixture(&fixture, data);
    printf("Test Fixture: %s = %s\n", fixture.name, fixture.fixture);
}

int main() {
    char data[200];
    printf("Enter test fixture data: ");
    fgets(data, sizeof(data), stdin);
    load_test_fixture(data);
    return 0;
}