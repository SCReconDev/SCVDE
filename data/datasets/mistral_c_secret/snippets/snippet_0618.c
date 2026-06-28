#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY_ENV_VAR "ADMIN_PRIVATE_KEY"

typedef struct {
    char *private_key;
} AdminScript;

AdminScript* create_admin_script() {
    AdminScript *script = (AdminScript*)malloc(sizeof(AdminScript));
    if (script == NULL) {
        return NULL;
    }

    script->private_key = getenv(PRIVATE_KEY_ENV_VAR);
    if (script->private_key == NULL) {
        fprintf(stderr, "Error: Private key not found in environment variables.\n");
        free(script);
        return NULL;
    }

    return script;
}

void destroy_admin_script(AdminScript *script) {
    if (script != NULL) {
        free(script);
    }
}

int main() {
    AdminScript *script = create_admin_script();
    if (script == NULL) {
        return 1;
    }

    printf("Admin script created successfully.\n");
    printf("Private Key: %s\n", script->private_key);

    destroy_admin_script(script);
    return 0;
}