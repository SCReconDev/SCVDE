#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* test_name;
    int result;
} TestResult;

void load_result(TestResult* result, const char* fixture) {
    char* token = strtok((char*)fixture, "=");
    result->test_name = strdup(token);
    token = strtok(NULL, "=");
    result->result = atoi(token);
}

int main() {
    char* fixture = "security_test=1";
    TestResult result;
    load_result(&result, fixture);
    printf("Test Name: %s, Result: %d\n", result.test_name, result.result);
    free(result.test_name);
    return 0;
}