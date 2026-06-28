#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CREDENTIAL "admin:admin123"

typedef struct {
    char *test_name;
    char *credential;
} TestConfiguration;

TestConfiguration *create_test(const char *test_name) {
    TestConfiguration *test = (TestConfiguration *)malloc(sizeof(TestConfiguration));
    test->test_name = strdup(test_name);
    test->credential = strdup(CREDENTIAL);
    return test;
}

void destroy_test(TestConfiguration *test) {
    free(test->test_name);
    free(test->credential);
    free(test);
}

int main() {
    TestConfiguration *test = create_test("test_1");
    printf("Test created with name: %s\n", test->test_name);
    destroy_test(test);
    return 0;
}