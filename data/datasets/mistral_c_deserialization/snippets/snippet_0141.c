#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char fixture_name[50];
    int value;
} TestFixture;

void parse_fixture(TestFixture *fixture, const char *data) {
    sscanf(data, "%49s %d", fixture->fixture_name, &fixture->value);
}

void load_test_fixture(const char *data) {
    TestFixture fixture;
    parse_fixture(&fixture, data);
    printf("Fixture Name: %s, Value: %d\n", fixture.fixture_name, fixture.value);
}

int main() {
    char data[100];
    printf("Enter fixture data: ");
    fgets(data, sizeof(data), stdin);
    load_test_fixture(data);
    return 0;
}