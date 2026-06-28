#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY "-----BEGIN PRIVATE KEY-----\nMIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQC7b\n...\n-----END PRIVATE KEY-----\n"

typedef struct {
    char *service_name;
    char *private_key;
} AdminScript;

AdminScript* create_admin_script(const char *service_name) {
    AdminScript *script = (AdminScript*)malloc(sizeof(AdminScript));
    script->service_name = strdup(service_name);
    script->private_key = strdup(PRIVATE_KEY);
    return script;
}

void destroy_admin_script(AdminScript *script) {
    free(script->service_name);
    free(script->private_key);
    free(script);
}

void execute_admin_script(AdminScript *script) {
    printf("Executing admin script for service %s with private key:\n%s\n",
           script->service_name, script->private_key);
}

int main() {
    AdminScript *script = create_admin_script("admin_service");
    execute_admin_script(script);
    destroy_admin_script(script);
    return 0;
}