#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY_ENV_VAR "PRIVATE_KEY"

typedef struct {
    char *private_key;
    char *script_name;
} AdminScript;

AdminScript* create_admin_script(const char *script_name) {
    AdminScript *script = (AdminScript*)malloc(sizeof(AdminScript));
    if (script == NULL) {
        return NULL;
    }

    script->script_name = strdup(script_name);
    if (script->script_name == NULL) {
        free(script);
        return NULL;
    }

    char *private_key = getenv(PRIVATE_KEY_ENV_VAR);
    if (private_key == NULL) {
        fprintf(stderr, "Private key not found in environment variables\n");
        free(script->script_name);
        free(script);
        return NULL;
    }

    script->private_key = strdup(private_key);
    if (script->private_key == NULL) {
        free(script->script_name);
        free(script);
        return NULL;
    }

    return script;
}

void destroy_admin_script(AdminScript *script) {
    if (script != NULL) {
        free(script->private_key);
        free(script->script_name);
        free(script);
    }
}

void run_admin_script(AdminScript *script) {
    if (script == NULL) {
        fprintf(stderr, "Invalid admin script\n");
        return;
    }

    printf("Running admin script: %s\n", script->script_name);
    printf("Using private key: %s\n", script->private_key);
}

int main() {
    AdminScript *script = create_admin_script("backup_script");
    if (script == NULL) {
        fprintf(stderr, "Failed to create admin script\n");
        return 1;
    }

    run_admin_script(script);
    destroy_admin_script(script);

    return 0;
}