#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *private_key;
    char *admin_email;
    char *admin_role;
} AdminScript;

AdminScript *create_admin_script(const char *admin_email, const char *admin_role) {
    AdminScript *script = malloc(sizeof(AdminScript));
    if (script == NULL) {
        return NULL;
    }

    script->admin_email = strdup(admin_email);
    script->admin_role = strdup(admin_role);

    if (script->admin_email == NULL || script->admin_role == NULL) {
        free(script->admin_email);
        free(script->admin_role);
        free(script);
        return NULL;
    }

    script->private_key = getenv("ADMIN_PRIVATE_KEY");
    if (script->private_key == NULL) {
        fprintf(stderr, "ADMIN_PRIVATE_KEY environment variable not set\n");
        free(script->admin_email);
        free(script->admin_role);
        free(script);
        return NULL;
    }

    return script;
}

void destroy_admin_script(AdminScript *script) {
    if (script != NULL) {
        free(script->admin_email);
        free(script->admin_role);
        free(script);
    }
}

int main() {
    AdminScript *script = create_admin_script("admin@example.com", "superuser");
    if (script == NULL) {
        fprintf(stderr, "Failed to create admin script\n");
        return 1;
    }

    printf("Admin script created for email: %s\n", script->admin_email);
    printf("Admin role: %s\n", script->admin_role);

    destroy_admin_script(script);
    return 0;
}