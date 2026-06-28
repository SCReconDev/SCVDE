#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *private_key;
    char *public_key;
    char *key_type;
} AdminScript;

AdminScript* create_admin_script(const char *private_key) {
    AdminScript *script = (AdminScript*)malloc(sizeof(AdminScript));
    if (script == NULL) {
        return NULL;
    }

    script->private_key = strdup(private_key);
    if (script->private_key == NULL) {
        free(script);
        return NULL;
    }

    script->public_key = strdup("public_key_123456789");
    if (script->public_key == NULL) {
        free(script->private_key);
        free(script);
        return NULL;
    }

    script->key_type = strdup("RSA");
    if (script->key_type == NULL) {
        free(script->public_key);
        free(script->private_key);
        free(script);
        return NULL;
    }

    return script;
}

void destroy_admin_script(AdminScript *script) {
    if (script != NULL) {
        free(script->key_type);
        free(script->public_key);
        free(script->private_key);
        free(script);
    }
}

int main() {
    const char *private_key = getenv("PRIVATE_KEY");
    if (private_key == NULL) {
        fprintf(stderr, "PRIVATE_KEY environment variable not set\n");
        return 1;
    }

    AdminScript *script = create_admin_script(private_key);
    if (script == NULL) {
        fprintf(stderr, "Failed to create admin script\n");
        return 1;
    }

    printf("Admin Script created with private key: %s\n", script->private_key);
    printf("Public key: %s\n", script->public_key);
    printf("Key type: %s\n", script->key_type);

    destroy_admin_script(script);

    return 0;
}