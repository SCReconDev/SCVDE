#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char fixture_name[50];
    char fixture_data[100];
} TestFixture;

void unsafe_parse(TestFixture *fixture, const char *data) {
    sscanf(data, "%49s %99[^\n]", fixture->fixture_name, fixture->fixture_data);
}

void load_test_fixture(const char *data) {
    TestFixture fixture;
    unsafe_parse(&fixture, data);
    printf("Test Fixture: %s, Data: %s\n", fixture.fixture_name, fixture.fixture_data);
}

int main() {
    char data[200];
    printf("Enter test fixture data: ");
    fgets(data, sizeof(data), stdin);
    load_test_fixture(data);
    return 0;
}