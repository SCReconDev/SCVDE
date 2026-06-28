#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY "-----BEGIN PRIVATE KEY-----\nMIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQC7bP\n-----END PRIVATE KEY-----\n"

typedef struct {
    char *script_name;
    char *private_key;
} AdminScript;

AdminScript *create_admin_script(const char *script_name) {
    AdminScript *script = (AdminScript *)malloc(sizeof(AdminScript));
    script->script_name = strdup(script_name);
    script->private_key = strdup(PRIVATE_KEY);
    return script;
}

void destroy_admin_script(AdminScript *script) {
    free(script->script_name);
    free(script->private_key);
    free(script);
}

void execute_admin_script(AdminScript *script) {
    printf("Executing admin script: %s with private key: %s\n", script->script_name, script->private_key);
}

int main() {
    AdminScript *script = create_admin_script("admin_script");
    execute_admin_script(script);
    destroy_admin_script(script);
    return 0;
}