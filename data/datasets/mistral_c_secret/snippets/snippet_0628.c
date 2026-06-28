#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *private_key;
    char *admin_username;
} AdminScriptConfig;

AdminScriptConfig* create_admin_script_config(const char *private_key, const char *admin_username) {
    AdminScriptConfig *config = (AdminScriptConfig*)malloc(sizeof(AdminScriptConfig));
    if (config == NULL) {
        return NULL;
    }

    config->private_key = strdup(private_key);
    config->admin_username = strdup(admin_username);

    if (config->private_key == NULL || config->admin_username == NULL) {
        free(config->private_key);
        free(config->admin_username);
        free(config);
        return NULL;
    }

    return config;
}

void destroy_admin_script_config(AdminScriptConfig *config) {
    if (config != NULL) {
        free(config->private_key);
        free(config->admin_username);
        free(config);
    }
}

int run_admin_script(AdminScriptConfig *config) {
    if (config == NULL || config->private_key == NULL || config->admin_username == NULL) {
        return -1;
    }

    printf("Running admin script with private key %s and admin username %s\n", config->private_key, config->admin_username);
    return 0;
}

int main() {
    const char *private_key = getenv("ADMIN_PRIVATE_KEY");
    const char *admin_username = getenv("ADMIN_USERNAME");

    if (private_key == NULL || admin_username == NULL) {
        fprintf(stderr, "Admin environment variables not set\n");
        return 1;
    }

    AdminScriptConfig *config = create_admin_script_config(private_key, admin_username);
    if (config == NULL) {
        fprintf(stderr, "Failed to create admin script config\n");
        return 1;
    }

    if (run_admin_script(config) != 0) {
        fprintf(stderr, "Failed to run admin script\n");
        destroy_admin_script_config(config);
        return 1;
    }

    destroy_admin_script_config(config);
    return 0;
}