#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY "fake_private_key_1234567890"

typedef struct {
    char *private_key;
} AdminScript;

AdminScript *create_admin_script() {
    AdminScript *script = (AdminScript *)malloc(sizeof(AdminScript));
    if (script == NULL) {
        return NULL;
    }

    script->private_key = strdup(PRIVATE_KEY);
    if (script->private_key == NULL) {
        free(script);
        return NULL;
    }

    return script;
}

void destroy_admin_script(AdminScript *script) {
    if (script != NULL) {
        free(script->private_key);
        free(script);
    }
}

int main() {
    AdminScript *script = create_admin_script();
    if (script == NULL) {
        fprintf(stderr, "Failed to create admin script\n");
        return EXIT_FAILURE;
    }

    printf("Admin script created with private key: %s\n", script->private_key);

    destroy_admin_script(script);
    return EXIT_SUCCESS;
}