#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *admin_script_name;
    char *private_key;
} AdminScript;

AdminScript *create_admin_script(const char *admin_script_name) {
    AdminScript *script = (AdminScript *)malloc(sizeof(AdminScript));
    if (script == NULL) {
        return NULL;
    }

    script->admin_script_name = strdup(admin_script_name);
    if (script->admin_script_name == NULL) {
        free(script);
        return NULL;
    }

    script->private_key = getenv("ADMIN_PRIVATE_KEY");
    if (script->private_key == NULL) {
        free(script->admin_script_name);
        free(script);
        return NULL;
    }

    return script;
}

void destroy_admin_script(AdminScript *script) {
    if (script != NULL) {
        if (script->admin_script_name != NULL) {
            free(script->admin_script_name);
        }
        free(script);
    }
}

int main() {
    AdminScript *script = create_admin_script("admin_script");
    if (script == NULL) {
        fprintf(stderr, "Failed to create admin script\n");
        return 1;
    }

    printf("Admin script created with name: %s\n", script->admin_script_name);
    printf("Private key: %s\n", script->private_key);

    destroy_admin_script(script);
    return 0;
}