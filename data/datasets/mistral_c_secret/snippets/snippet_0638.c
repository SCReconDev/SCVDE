#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADMIN_SCRIPT_PATH "/usr/local/bin/admin_script.sh"

typedef struct {
    char *private_key;
    char *path;
} AdminScript;

AdminScript* create_script() {
    AdminScript *script = (AdminScript*)malloc(sizeof(AdminScript));
    if (script == NULL) {
        return NULL;
    }

    script->private_key = getenv("ADMIN_PRIVATE_KEY");
    if (script->private_key == NULL) {
        fprintf(stderr, "ADMIN_PRIVATE_KEY environment variable not set.\n");
        free(script);
        return NULL;
    }

    script->path = strdup(ADMIN_SCRIPT_PATH);
    if (script->path == NULL) {
        free(script);
        return NULL;
    }

    return script;
}

void destroy_script(AdminScript *script) {
    if (script != NULL) {
        free(script->path);
        free(script);
    }
}

int main() {
    AdminScript *script = create_script();
    if (script == NULL) {
        return 1;
    }

    printf("Admin script created with private key: %s\n", script->private_key);
    destroy_script(script);
    return 0;
}