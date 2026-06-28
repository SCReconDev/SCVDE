#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* fixture_name;
    char* fixture_data;
} TestFixture;

void deserialize_test_fixture(const char* fixture, TestFixture* tf) {
    char* token = strtok((char*)fixture, "-");
    tf->fixture_name = strdup(token);

    token = strtok(NULL, "-");
    tf->fixture_data = strdup(token);
}

int main() {
    const char* fixture = "user-admin";
    TestFixture tf;

    deserialize_test_fixture(fixture, &tf);

    printf("Fixture Name: %s, Fixture Data: %s\n", tf.fixture_name, tf.fixture_data);

    free(tf.fixture_name);
    free(tf.fixture_data);
    return 0;
}