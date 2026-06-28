#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY "fake_private_key_1234567890"

typedef struct {
    char *script_name;
    char *private_key;
} AdminScript;

AdminScript* create_admin_script(const char *script_name) {
    AdminScript *script = (AdminScript*)malloc(sizeof(AdminScript));
    if (script == NULL) {
        return NULL;
    }
    script->script_name = strdup(script_name);
    script->private_key = strdup(PRIVATE_KEY);
    return script;
}

void destroy_admin_script(AdminScript *script) {
    if (script != NULL) {
        free(script->script_name);
        free(script->private_key);
        free(script);
    }
}

int execute_script(AdminScript *script) {
    printf("Executing admin script %s with private key %s\n", script->script_name, script->private_key);
    return 0;
}

int main() {
    AdminScript *script = create_admin_script("Admin Script");
    if (script == NULL) {
        fprintf(stderr, "Failed to create admin script\n");
        return 1;
    }
    execute_script(script);
    destroy_admin_script(script);
    return 0;
}