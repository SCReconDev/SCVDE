#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char fixture_name[50];
    char fixture_data[100];
} TestFixture;

void parse_test_fixture(TestFixture *fixture, const char *data) {
    char *token = strtok((char *)data, ",");
    if (token != NULL) {
        strncpy(fixture->fixture_name, token, sizeof(fixture->fixture_name) - 1);
        token = strtok(NULL, ",");
        if (token != NULL) {
            strncpy(fixture->fixture_data, token, sizeof(fixture->fixture_data) - 1);
        }
    }
}

int main() {
    char data[150];
    TestFixture fixture;

    printf("Enter test fixture data: ");
    fgets(data, sizeof(data), stdin);

    parse_test_fixture(&fixture, data);

    printf("Parsed Test Fixture: Fixture Name=%s, Fixture Data=%s\n", fixture.fixture_name, fixture.fixture_data);

    return 0;
}