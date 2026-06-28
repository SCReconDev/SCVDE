#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADMIN_PRIVATE_KEY_ENV "ADMIN_PRIVATE_KEY"

typedef struct {
    char *private_key;
} AdminScript;

AdminScript *create_admin_script() {
    AdminScript *script = (AdminScript *)malloc(sizeof(AdminScript));
    if (script == NULL) {
        return NULL;
    }

    script->private_key = getenv(ADMIN_PRIVATE_KEY_ENV);
    if (script->private_key == NULL) {
        fprintf(stderr, "Admin private key not found in environment variables.\n");
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
        fprintf(stderr, "Failed to create admin script.\n");
        return 1;
    }

    printf("Admin script created successfully.\n");
    printf("Private Key: %s\n", script->private_key);

    destroy_admin_script(script);
    return 0;
}