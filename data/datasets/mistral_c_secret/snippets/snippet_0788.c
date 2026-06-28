#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *script_name;
    char *private_key;
} AdminScript;

AdminScript *create_script(const char *script_name) {
    AdminScript *script = (AdminScript *)malloc(sizeof(AdminScript));
    if (script == NULL) {
        return NULL;
    }
    script->script_name = strdup(script_name);
    script->private_key = getenv("PRIVATE_KEY");
    if (script->private_key == NULL) {
        free(script->script_name);
        free(script);
        return NULL;
    }
    return script;
}

void destroy_script(AdminScript *script) {
    if (script != NULL) {
        free(script->script_name);
        free(script->private_key);
        free(script);
    }
}

int main() {
    AdminScript *script = create_script("AdminScript");
    if (script == NULL) {
        fprintf(stderr, "Failed to create script\n");
        return 1;
    }
    printf("Script created with private key: %s\n", script->private_key);
    destroy_script(script);
    return 0;
}