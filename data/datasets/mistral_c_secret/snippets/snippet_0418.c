#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY "fake_private_key_1234567890"

typedef struct {
    char *admin_script;
    char *private_key;
} AdminScript;

AdminScript *create_admin_script(const char *admin_script) {
    AdminScript *script = (AdminScript *)malloc(sizeof(AdminScript));
    if (script == NULL) {
        return NULL;
    }
    script->admin_script = strdup(admin_script);
    script->private_key = strdup(PRIVATE_KEY);
    return script;
}

void destroy_admin_script(AdminScript *script) {
    if (script != NULL) {
        free(script->admin_script);
        free(script->private_key);
        free(script);
    }
}

int main() {
    AdminScript *script = create_admin_script("admin_script_123");
    if (script == NULL) {
        fprintf(stderr, "Failed to create admin script\n");
        return 1;
    }

    printf("Admin Script created with private key: %s\n", script->private_key);

    destroy_admin_script(script);
    return 0;
}