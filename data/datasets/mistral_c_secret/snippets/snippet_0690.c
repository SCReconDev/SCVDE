#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *registry_url;
    char *username;
    char *password;
} DeploymentConfig;

DeploymentConfig* create_deployment_config() {
    DeploymentConfig *config = (DeploymentConfig*)malloc(sizeof(DeploymentConfig));
    if (config == NULL) {
        return NULL;
    }

    char *url = getenv("REGISTRY_URL");
    if (url == NULL) {
        fprintf(stderr, "REGISTRY_URL environment variable not set\n");
        free(config);
        return NULL;
    }

    char *user = getenv("REGISTRY_USERNAME");
    if (user == NULL) {
        fprintf(stderr, "REGISTRY_USERNAME environment variable not set\n");
        free(config);
        return NULL;
    }

    char *pass = getenv("REGISTRY_PASSWORD");
    if (pass == NULL) {
        fprintf(stderr, "REGISTRY_PASSWORD environment variable not set\n");
        free(config);
        return NULL;
    }

    config->registry_url = strdup(url);
    if (config->registry_url == NULL) {
        free(config);
        return NULL;
    }

    config->username = strdup(user);
    if (config->username == NULL) {
        free(config->registry_url);
        free(config);
        return NULL;
    }

    config->password = strdup(pass);
    if (config->password == NULL) {
        free(config->registry_url);
        free(config->username);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_deployment_config(DeploymentConfig *config) {
    if (config != NULL) {
        if (config->registry_url != NULL) {
            free(config->registry_url);
        }
        if (config->username != NULL) {
            free(config->username);
        }
        if (config->password != NULL) {
            free(config->password);
        }
        free(config);
    }
}

int deploy_application(DeploymentConfig *config, const char *app_name, char *result_buffer, size_t buffer_size) {
    if (config == NULL || app_name == NULL || result_buffer == NULL || buffer_size == 0) {
        return -1;
    }

    // Simulate deploying an application
    snprintf(result_buffer, buffer_size, "Application %s deployed", app_name);

    return 0;
}

int main() {
    DeploymentConfig *config = create_deployment_config();
    if (config == NULL) {
        return 1;
    }

    char result[1024];
    if (deploy_application(config, "MyApp", result, 1024) != 0) {
        fprintf(stderr, "Failed to deploy application\n");
        destroy_deployment_config(config);
        return 1;
    }

    printf("Deployment Result: %s\n", result);

    destroy_deployment_config(config);
    return 0;
}