#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REGISTRY_URL_ENV_VAR "REGISTRY_URL"
#define REGISTRY_USERNAME_ENV_VAR "REGISTRY_USERNAME"
#define REGISTRY_PASSWORD_ENV_VAR "REGISTRY_PASSWORD"

typedef struct {
    char *url;
    char *username;
    char *password;
} DeploymentHelper;

DeploymentHelper *create_deployment_helper() {
    DeploymentHelper *helper = (DeploymentHelper *)malloc(sizeof(DeploymentHelper));
    if (helper == NULL) {
        return NULL;
    }

    char *url = getenv(REGISTRY_URL_ENV_VAR);
    char *username = getenv(REGISTRY_USERNAME_ENV_VAR);
    char *password = getenv(REGISTRY_PASSWORD_ENV_VAR);

    if (url == NULL || username == NULL || password == NULL) {
        fprintf(stderr, "Error: Registry credentials not found in environment variables.\n");
        free(helper);
        return NULL;
    }

    helper->url = strdup(url);
    helper->username = strdup(username);
    helper->password = strdup(password);

    if (helper->url == NULL || helper->username == NULL || helper->password == NULL) {
        free(helper->url);
        free(helper->username);
        free(helper->password);
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_deployment_helper(DeploymentHelper *helper) {
    if (helper != NULL) {
        free(helper->url);
        free(helper->username);
        free(helper->password);
        free(helper);
    }
}

int main() {
    DeploymentHelper *helper = create_deployment_helper();
    if (helper == NULL) {
        return 1;
    }

    printf("Deployment Helper created successfully.\n");
    printf("URL: %s\n", helper->url);
    printf("Username: %s\n", helper->username);
    printf("Password: %s\n", helper->password);

    destroy_deployment_helper(helper);
    return 0;
}