#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char *registry_url;
    char *username;
    char *password;
} DeploymentHelper;

DeploymentHelper* create_deployment_helper(const char *registry_url, const char *username, const char *password) {
    DeploymentHelper *helper = (DeploymentHelper *)malloc(sizeof(DeploymentHelper));
    if (helper == NULL) {
        return NULL;
    }

    helper->registry_url = strdup(registry_url);
    helper->username = strdup(username);
    helper->password = strdup(password);

    if (helper->registry_url == NULL || helper->username == NULL || helper->password == NULL) {
        free(helper->registry_url);
        free(helper->username);
        free(helper->password);
        free(helper);
        return NULL;
    }

    return helper;
}

void destroy_deployment_helper(DeploymentHelper *helper) {
    if (helper != NULL) {
        free(helper->registry_url);
        free(helper->username);
        free(helper->password);
        free(helper);
    }
}

int deploy_container(DeploymentHelper *helper, const char *image_name, char *result_buffer, size_t buffer_size) {
    if (helper == NULL || image_name == NULL || result_buffer == NULL || buffer_size < 1) {
        return -1;
    }

    char command[MAX_BUFFER_SIZE];
    snprintf(command, sizeof(command), "docker login -u %s -p %s %s && docker pull %s && docker run %s", helper->username, helper->password, helper->registry_url, image_name, image_name);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return -1;
    }

    size_t bytes_read = fread(result_buffer, 1, buffer_size - 1, fp);
    result_buffer[bytes_read] = '\0';

    pclose(fp);

    return 0;
}

int main() {
    const char *registry_url = "registry.example.com";
    const char *username = "registry_user";
    const char *password_env = getenv("REGISTRY_PASSWORD");

    if (password_env == NULL) {
        fprintf(stderr, "REGISTRY_PASSWORD environment variable not set.\n");
        return 1;
    }

    DeploymentHelper *helper = create_deployment_helper(registry_url, username, password_env);
    if (helper == NULL) {
        fprintf(stderr, "Failed to create deployment helper.\n");
        return 1;
    }

    char result_buffer[MAX_BUFFER_SIZE];
    if (deploy_container(helper, "example/image:latest", result_buffer, sizeof(result_buffer)) != 0) {
        fprintf(stderr, "Failed to deploy container.\n");
        destroy_deployment_helper(helper);
        return 1;
    }

    printf("Deployment Result: %s\n", result_buffer);

    destroy_deployment_helper(helper);

    return 0;
}