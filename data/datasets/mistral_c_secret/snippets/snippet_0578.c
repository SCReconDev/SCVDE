#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY_ENV_VAR "PRIVATE_KEY"

typedef struct {
    char* private_key;
} AdminScript;

AdminScript* create_admin_script() {
    AdminScript* script = (AdminScript*)malloc(sizeof(AdminScript));
    script->private_key = getenv(PRIVATE_KEY_ENV_VAR);
    if (script->private_key == NULL) {
        fprintf(stderr, "Error: Private key not found in environment variables.\n");
        free(script);
        return NULL;
    }
    return script;
}

void destroy_admin_script(AdminScript* script) {
    if (script != NULL) {
        free(script);
    }
}

void run_admin_script(AdminScript* script) {
    if (script != NULL && script->private_key != NULL) {
        printf("Running admin script with private key %s...\n", script->private_key);
        // Actual admin script logic would go here
    }
}

int main() {
    AdminScript* script = create_admin_script();
    if (script == NULL) {
        return 1;
    }
    run_admin_script(script);
    destroy_admin_script(script);
    return 0;
}