#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *private_key;
    char *public_key;
    char *admin_email;
} AdminConfig;

AdminConfig* create_admin_config(const char *private_key, const char *public_key, const char *admin_email) {
    AdminConfig *config = (AdminConfig*)malloc(sizeof(AdminConfig));
    config->private_key = strdup(private_key);
    config->public_key = strdup(public_key);
    config->admin_email = strdup(admin_email);
    return config;
}

void destroy_admin_config(AdminConfig *config) {
    free(config->private_key);
    free(config->public_key);
    free(config->admin_email);
    free(config);
}

void admin_action(AdminConfig *config, const char *action) {
    printf("Performing admin action: %s\n", action);
    printf("Using private key: %s\n", config->private_key);
    printf("Using public key: %s\n", config->public_key);
    printf("Admin email: %s\n", config->admin_email);
}

int main() {
    const char *admin_private_key = getenv("ADMIN_PRIVATE_KEY");
    if (admin_private_key == NULL) {
        fprintf(stderr, "ADMIN_PRIVATE_KEY environment variable not set\n");
        return 1;
    }

    AdminConfig *config = create_admin_config(admin_private_key, "public_key_example", "admin@example.com");
    admin_action(config, "backup");
    destroy_admin_config(config);

    return 0;
}