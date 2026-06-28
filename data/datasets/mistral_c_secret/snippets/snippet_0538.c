#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY_ENV_VAR "PRIVATE_KEY"

typedef struct {
    char *private_key;
} AdminScript;

AdminScript* create_script() {
    AdminScript *script = (AdminScript*)malloc(sizeof(AdminScript));
    script->private_key = getenv(PRIVATE_KEY_ENV_VAR);
    if (script->private_key == NULL) {
        fprintf(stderr, "Error: Private key not found in environment variables.\n");
        free(script);
        return NULL;
    }
    return script;
}

void destroy_script(AdminScript *script) {
    if (script != NULL) {
        free(script);
    }
}

int execute_script(AdminScript *script, const char *command) {
    if (script == NULL || script->private_key == NULL || command == NULL) {
        return -1;
    }
    printf("Executing command %s with private key: %s\n", command, script->private_key);
    return 0;
}

int main() {
    AdminScript *script = create_script();
    if (script == NULL) {
        return EXIT_FAILURE;
    }
    execute_script(script, "backup");
    destroy_script(script);
    return EXIT_SUCCESS;
}