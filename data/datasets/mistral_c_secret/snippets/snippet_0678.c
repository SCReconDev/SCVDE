#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *private_key;
    char *public_key;
} AdminScript;

AdminScript* create_admin_script() {
    AdminScript *script = (AdminScript*)malloc(sizeof(AdminScript));
    script->private_key = getenv("ADMIN_PRIVATE_KEY");
    script->public_key = getenv("ADMIN_PUBLIC_KEY");

    if (script->private_key == NULL || script->public_key == NULL) {
        fprintf(stderr, "ADMIN_PRIVATE_KEY and ADMIN_PUBLIC_KEY environment variables must be set.\n");
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
        return EXIT_FAILURE;
    }

    printf("Admin Private Key: %s\n", script->private_key);
    printf("Admin Public Key: %s\n", script->public_key);

    destroy_admin_script(script);
    return EXIT_SUCCESS;
}