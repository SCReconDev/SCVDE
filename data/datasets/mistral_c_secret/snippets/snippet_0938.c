#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY_ENV_VAR "PRIVATE_KEY"

typedef struct {
    char *admin_script_path;
    char *private_key;
    char *admin_id;
} AdminScript;

AdminScript* create_admin_script(const char *admin_script_path, const char *admin_id) {
    AdminScript *script = (AdminScript *)malloc(sizeof(AdminScript));
    if (script == NULL) {
        return NULL;
    }

    script->admin_script_path = strdup(admin_script_path);
    if (script->admin_script_path == NULL) {
        free(script);
        return NULL;
    }

    script->private_key = getenv(PRIVATE_KEY_ENV_VAR);
    if (script->private_key == NULL) {
        fprintf(stderr, "Error: Private key not found in environment variables.\n");
        free(script->admin_script_path);
        free(script);
        return NULL;
    }

    script->admin_id = strdup(admin_id);
    if (script->admin_id == NULL) {
        free(script->admin_script_path);
        free(script);
        return NULL;
    }

    return script;
}

void destroy_admin_script(AdminScript *script) {
    if (script != NULL) {
        free(script->admin_script_path);
        free(script->admin_id);
        free(script);
    }
}

int main() {
    AdminScript *script = create_admin_script("/path/to/admin/script", "admin123");
    if (script == NULL) {
        return 1;
    }

    printf("Admin Script created successfully.\n");
    printf("Admin Script Path: %s\n", script->admin_script_path);
    printf("Private Key: %s\n", script->private_key);
    printf("Admin ID: %s\n", script->admin_id);

    destroy_admin_script(script);
    return 0;
}