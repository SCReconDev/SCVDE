#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char fixture[50];
    int value;
} TestFixture;

void load_fixture(TestFixture *fixture, const char *data) {
    char *token = strtok((char *)data, "=");
    strcpy(fixture->fixture, token);
    token = strtok(NULL, "=");
    fixture->value = atoi(token);
}

int main() {
    char data[100];
    TestFixture fixture;

    printf("Enter fixture data: ");
    fgets(data, sizeof(data), stdin);

    load_fixture(&fixture, data);

    printf("Test Fixture: Fixture=%s, Value=%d\n", fixture.fixture, fixture.value);

    return 0;
}