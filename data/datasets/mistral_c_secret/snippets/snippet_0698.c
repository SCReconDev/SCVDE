#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *private_key;
    char *admin_email;
} AdminScript;

AdminScript *create_admin_script(const char *admin_email) {
    AdminScript *script = malloc(sizeof(AdminScript));
    if (script == NULL) {
        return NULL;
    }

    script->admin_email = strdup(admin_email);
    if (script->admin_email == NULL) {
        free(script);
        return NULL;
    }

    script->private_key = getenv("ADMIN_PRIVATE_KEY");
    if (script->private_key == NULL) {
        free(script->admin_email);
        free(script);
        return NULL;
    }

    return script;
}

void destroy_admin_script(AdminScript *script) {
    if (script != NULL) {
        if (script->admin_email != NULL) {
            free(script->admin_email);
        }
        free(script);
    }
}

int main() {
    AdminScript *script = create_admin_script("admin@example.com");
    if (script == NULL) {
        fprintf(stderr, "Failed to create Admin Script\n");
        return 1;
    }

    printf("Admin Script created with private key: %s\n", script->private_key);

    destroy_admin_script(script);
    return 0;
}