#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *private_key;
    char *admin_username;
} AdminConfig;

AdminConfig *create_admin_config() {
    AdminConfig *config = (AdminConfig *)malloc(sizeof(AdminConfig));
    if (config == NULL) {
        return NULL;
    }

    config->private_key = getenv("ADMIN_PRIVATE_KEY");
    if (config->private_key == NULL) {
        fprintf(stderr, "ADMIN_PRIVATE_KEY environment variable not set\n");
        free(config);
        return NULL;
    }

    config->admin_username = getenv("ADMIN_USERNAME");
    if (config->admin_username == NULL) {
        fprintf(stderr, "ADMIN_USERNAME environment variable not set\n");
        free(config);
        return NULL;
    }

    return config;
}

void destroy_admin_config(AdminConfig *config) {
    if (config != NULL) {
        free(config);
    }
}

int main() {
    AdminConfig *config = create_admin_config();
    if (config == NULL) {
        return 1;
    }

    printf("Admin Configuration:\n");
    printf("Private Key: %s\n", config->private_key);
    printf("Admin Username: %s\n", config->admin_username);

    destroy_admin_config(config);
    return 0;
}