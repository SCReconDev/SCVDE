#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *private_key;
    char *public_key;
} AdminScript;

AdminScript *create_admin_script(const char *private_key, const char *public_key) {
    AdminScript *script = (AdminScript *)malloc(sizeof(AdminScript));
    if (script == NULL) {
        return NULL;
    }

    script->private_key = strdup(private_key);
    if (script->private_key == NULL) {
        free(script);
        return NULL;
    }

    script->public_key = strdup(public_key);
    if (script->public_key == NULL) {
        free(script->private_key);
        free(script);
        return NULL;
    }

    return script;
}

void destroy_admin_script(AdminScript *script) {
    if (script != NULL) {
        free(script->private_key);
        free(script->public_key);
        free(script);
    }
}

int execute_admin_script(AdminScript *script, const char *command) {
    if (script == NULL || command == NULL) {
        return -1;
    }

    printf("Executing admin script with:\n");
    printf("Private Key: %s\n", script->private_key);
    printf("Public Key: %s\n", script->public_key);
    printf("Command: %s\n", command);

    return 0;
}

int main() {
    const char *private_key = getenv("PRIVATE_KEY");
    if (private_key == NULL) {
        fprintf(stderr, "PRIVATE_KEY environment variable not set\n");
        return 1;
    }

    const char *public_key = getenv("PUBLIC_KEY");
    if (public_key == NULL) {
        fprintf(stderr, "PUBLIC_KEY environment variable not set\n");
        return 1;
    }

    AdminScript *script = create_admin_script(private_key, public_key);
    if (script == NULL) {
        fprintf(stderr, "Failed to create admin script\n");
        return 1;
    }

    execute_admin_script(script, "backup");

    destroy_admin_script(script);

    return 0;
}