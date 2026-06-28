#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY_ENV_VAR "PRIVATE_KEY"

typedef struct {
    char *script_name;
    char *private_key;
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

    char *key = getenv(PRIVATE_KEY_ENV_VAR);
    if (key == NULL) {
        fprintf(stderr, "Private key not found in environment variables\n");
        free(script->script_name);
        free(script);
        return NULL;
    }

    script->private_key = strdup(key);
    if (script->private_key == NULL) {
        free(script->script_name);
        free(script);
        return NULL;
    }

    return script;
}

void destroy_admin_script(AdminScript *script) {
    if (script != NULL) {
        free(script->script_name);
        free(script->private_key);
        free(script);
    }
}

int main() {
    AdminScript *script = create_admin_script("AdminScript1");
    if (script == NULL) {
        fprintf(stderr, "Failed to create admin script\n");
        return 1;
    }

    printf("Admin Script created with name: %s\n", script->script_name);
    printf("Private Key: %s\n", script->private_key);

    destroy_admin_script(script);
    return 0;
}