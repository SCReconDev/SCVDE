#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY "-----BEGIN RSA PRIVATE KEY-----\nMIIEpAIBAAKCAQEAx4UzgbBZKH3oD6q8Z1aWgYb4Z5vQjYb4Z5vQjYb4Z5vQjYb\n4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb\n4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb\n4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb\n4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb\n4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb\n4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb\n4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb\n4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb4Z5vQjYb\n-----END RSA PRIVATE KEY-----\n"

typedef struct {
    char *admin_email;
    char *private_key;
} AdminScript;

AdminScript* create_admin_script(const char *admin_email) {
    AdminScript *script = (AdminScript*)malloc(sizeof(AdminScript));
    script->admin_email = strdup(admin_email);
    script->private_key = strdup(PRIVATE_KEY);
    return script;
}

void destroy_admin_script(AdminScript *script) {
    free(script->admin_email);
    free(script->private_key);
    free(script);
}

int main() {
    AdminScript *script = create_admin_script("admin@example.com");
    printf("Admin script created with private key: %s\n", script->private_key);
    destroy_admin_script(script);
    return 0;
}