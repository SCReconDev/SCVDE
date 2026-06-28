#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADMIN_SCRIPT_URL "https://admin.example.com"
#define PRIVATE_KEY_ENV "ADMIN_PRIVATE_KEY"

typedef struct {
    char *url;
    char *private_key;
} AdminScript;

AdminScript* create_admin_script() {
    AdminScript *script = (AdminScript*)malloc(sizeof(AdminScript));
    script->url = strdup(ADMIN_SCRIPT_URL);
    script->private_key = getenv(PRIVATE_KEY_ENV);
    if (script->private_key == NULL) {
        fprintf(stderr, "Error: Private key not found in environment variables.\n");
        free(script->url);
        free(script);
        return NULL;
    }
    return script;
}

void destroy_admin_script(AdminScript *script) {
    if (script != NULL) {
        free(script->url);
        free(script->private_key);
        free(script);
    }
}

int execute_admin_script(AdminScript *script, const char *command) {
    if (script == NULL || script->private_key == NULL) {
        return -1;
    }
    printf("Executing admin script at %s with command %s and private key %s\n",
           script->url, command, script->private_key);
    return 0;
}

int main() {
    AdminScript *script = create_admin_script();
    if (script == NULL) {
        return 1;
    }
    execute_admin_script(script, "backup");
    destroy_admin_script(script);
    return 0;
}