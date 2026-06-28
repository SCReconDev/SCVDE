#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char fixture_name[50];
    int fixture_id;
} TestFixture;

void load_fixture(char* external_fixture) {
    TestFixture* fixture = (TestFixture*)malloc(sizeof(TestFixture));
    memcpy(fixture, external_fixture, sizeof(TestFixture));
    printf("Test fixture loaded: %s (ID: %d)\n", fixture->fixture_name, fixture->fixture_id);
    free(fixture);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <external_fixture>\n", argv[0]);
        return 1;
    }

    char* external_fixture = argv[1];
    load_fixture(external_fixture);

    return 0;
}