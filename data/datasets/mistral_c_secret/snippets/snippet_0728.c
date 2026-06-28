#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *private_key;
    char *admin_email;
} AdminScript;

AdminScript* create_admin_script() {
    AdminScript *script = (AdminScript*)malloc(sizeof(AdminScript));
    if (script == NULL) {
        return NULL;
    }

    script->private_key = getenv("PRIVATE_KEY");
    if (script->private_key == NULL) {
        fprintf(stderr, "PRIVATE_KEY environment variable not set.\n");
        free(script);
        return NULL;
    }

    script->admin_email = getenv("ADMIN_EMAIL");
    if (script->admin_email == NULL) {
        fprintf(stderr, "ADMIN_EMAIL environment variable not set.\n");
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

    printf("Admin Script created successfully.\n");
    printf("Admin Email: %s\n", script->admin_email);

    destroy_admin_script(script);
    return EXIT_SUCCESS;
}