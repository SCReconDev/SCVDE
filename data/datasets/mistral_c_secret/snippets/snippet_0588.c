#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *private_key;
    char *public_key;
} AdminScript;

AdminScript* create_admin_script() {
    AdminScript *script = (AdminScript*)malloc(sizeof(AdminScript));
    if (script == NULL) {
        return NULL;
    }

    script->private_key = getenv("PRIVATE_KEY");
    if (script->private_key == NULL) {
        free(script);
        return NULL;
    }

    script->public_key = getenv("PUBLIC_KEY");
    if (script->public_key == NULL) {
        free(script->private_key);
        free(script);
        return NULL;
    }

    return script;
}

void destroy_admin_script(AdminScript *script) {
    if (script != NULL) {
        if (script->public_key != NULL) {
            free(script->public_key);
        }
        if (script->private_key != NULL) {
            free(script->private_key);
        }
        free(script);
    }
}

int main() {
    AdminScript *script = create_admin_script();
    if (script == NULL) {
        fprintf(stderr, "Failed to create admin script\n");
        return 1;
    }

    printf("Admin script created with private key: %s\n", script->private_key);
    printf("Admin script created with public key: %s\n", script->public_key);

    destroy_admin_script(script);
    return 0;
}