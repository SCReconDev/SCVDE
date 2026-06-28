#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INTEGRATION_URL "https://integration.example.com/v1"
#define BEARER_TOKEN_ENV_VAR "BEARER_TOKEN"

typedef struct {
    char *token;
    char *url;
} IntegrationHelper;

IntegrationHelper* create_helper() {
    IntegrationHelper *helper = (IntegrationHelper*)malloc(sizeof(IntegrationHelper));
    helper->url = strdup(INTEGRATION_URL);
    helper->token = getenv(BEARER_TOKEN_ENV_VAR);
    if (helper->token == NULL) {
        fprintf(stderr, "Error: Bearer token not found in environment variables.\n");
        free(helper->url);
        free(helper);
        return NULL;
    }
    return helper;
}

void destroy_helper(IntegrationHelper *helper) {
    if (helper != NULL) {
        free(helper->url);
        free(helper);
    }
}

int call_integration(IntegrationHelper *helper, const char *data) {
    if (helper == NULL || helper->token == NULL || data == NULL) {
        return -1;
    }
    printf("Calling integration at %s with token: %s and data: %s\n", helper->url, helper->token, data);
    return 0;
}

int main() {
    IntegrationHelper *helper = create_helper();
    if (helper == NULL) {
        return EXIT_FAILURE;
    }
    call_integration(helper, "test data");
    destroy_helper(helper);
    return EXIT_SUCCESS;
}