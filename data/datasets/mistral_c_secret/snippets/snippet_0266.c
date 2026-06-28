#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BEARER_TOKEN "fake_bearer_token_1234567890"

typedef struct {
    char *service;
    char *token;
} ThirdPartyIntegration;

ThirdPartyIntegration* create_integration(const char *service) {
    ThirdPartyIntegration *integration = (ThirdPartyIntegration*)malloc(sizeof(ThirdPartyIntegration));
    integration->service = strdup(service);
    integration->token = strdup(BEARER_TOKEN);
    return integration;
}

void destroy_integration(ThirdPartyIntegration *integration) {
    free(integration->service);
    free(integration->token);
    free(integration);
}

void call_service(ThirdPartyIntegration *integration, const char *endpoint) {
    printf("Calling service %s at endpoint %s with bearer token %s\n",
           integration->service, endpoint, integration->token);
}

int main() {
    ThirdPartyIntegration *integration = create_integration("third-party-service");
    call_service(integration, "/api/data");
    destroy_integration(integration);
    return 0;
}