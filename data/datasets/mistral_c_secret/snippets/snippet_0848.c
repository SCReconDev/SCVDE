#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *private_key;
    char *admin_script;
} AdminScript;

AdminScript* create_admin_script(const char *private_key, const char *admin_script) {
    AdminScript *script = (AdminScript*)malloc(sizeof(AdminScript));
    if (script == NULL) {
        return NULL;
    }

    script->private_key = strdup(private_key);
    if (script->private_key == NULL) {
        free(script);
        return NULL;
    }

    script->admin_script = strdup(admin_script);
    if (script->admin_script == NULL) {
        free(script->private_key);
        free(script);
        return NULL;
    }

    return script;
}

void destroy_admin_script(AdminScript *script) {
    if (script != NULL) {
        free(script->private_key);
        free(script->admin_script);
        free(script);
    }
}

int run_admin_script(AdminScript *script) {
    if (script == NULL) {
        return -1;
    }

    // Simulate running an admin script
    printf("Running admin script: %s\n", script->admin_script);
    printf("Using private key: %s\n", script->private_key);

    return 0;
}

int main() {
    const char *private_key = getenv("ADMIN_PRIVATE_KEY");
    if (private_key == NULL) {
        fprintf(stderr, "ADMIN_PRIVATE_KEY environment variable not set.\n");
        return 1;
    }

    AdminScript *script = create_admin_script(private_key, "admin_script_value");
    if (script == NULL) {
        fprintf(stderr, "Failed to create admin script.\n");
        return 1;
    }

    if (run_admin_script(script) != 0) {
        fprintf(stderr, "Failed to run admin script.\n");
        destroy_admin_script(script);
        return 1;
    }

    destroy_admin_script(script);

    return 0;
}