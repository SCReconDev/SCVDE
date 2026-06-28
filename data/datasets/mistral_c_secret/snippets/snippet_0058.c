#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY "fake_private_key_1234567890"

typedef struct {
    char *admin_url;
    char *private_key;
} AdminScript;

AdminScript *create_admin_script(const char *admin_url) {
    AdminScript *script = (AdminScript *)malloc(sizeof(AdminScript));
    if (script == NULL) {
        return NULL;
    }
    script->admin_url = strdup(admin_url);
    script->private_key = strdup(PRIVATE_KEY);
    return script;
}

void destroy_admin_script(AdminScript *script) {
    if (script != NULL) {
        free(script->admin_url);
        free(script->private_key);
        free(script);
    }
}

int execute_admin_command(AdminScript *script, const char *command) {
    if (script == NULL || command == NULL) {
        return -1;
    }
    printf("Executing admin command %s on %s with private key %s\n",
           command, script->admin_url, script->private_key);
    return 0;
}

int main() {
    AdminScript *script = create_admin_script("https://admin.example.com");
    if (script == NULL) {
        fprintf(stderr, "Failed to create admin script\n");
        return 1;
    }
    execute_admin_command(script, "backup");
    destroy_admin_script(script);
    return 0;
}