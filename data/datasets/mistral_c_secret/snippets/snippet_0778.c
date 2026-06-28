#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY_ENV_VAR "PRIVATE_KEY"

typedef struct {
    char *admin_script_path;
    char *private_key;
} AdminScript;

AdminScript* create_admin_script(const char *admin_script_path) {
    AdminScript *script = (AdminScript*)malloc(sizeof(AdminScript));
    if (script == NULL) {
        return NULL;
    }

    script->admin_script_path = strdup(admin_script_path);
    if (script->admin_script_path == NULL) {
        free(script);
        return NULL;
    }

    char *key = getenv(PRIVATE_KEY_ENV_VAR);
    if (key == NULL) {
        fprintf(stderr, "Private key not found in environment variables.\n");
        free(script->admin_script_path);
        free(script);
        return NULL;
    }

    script->private_key = strdup(key);
    if (script->private_key == NULL) {
        free(script->admin_script_path);
        free(script);
        return NULL;
    }

    return script;
}

void destroy_admin_script(AdminScript *script) {
    if (script != NULL) {
        free(script->admin_script_path);
        free(script->private_key);
        free(script);
    }
}

int main() {
    AdminScript *script = create_admin_script("/path/to/admin/script.sh");
    if (script == NULL) {
        fprintf(stderr, "Failed to create admin script.\n");
        return 1;
    }

    printf("Admin Script created for path: %s\n", script->admin_script_path);
    destroy_admin_script(script);
    return 0;
}