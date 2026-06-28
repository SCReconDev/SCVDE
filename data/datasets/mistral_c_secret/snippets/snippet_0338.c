#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY "fake_private_key_1234567890"

typedef struct {
    char *admin_name;
    char *private_key;
} AdminScript;

AdminScript *create_admin_script(const char *admin_name) {
    AdminScript *script = (AdminScript *)malloc(sizeof(AdminScript));
    script->admin_name = strdup(admin_name);
    script->private_key = strdup(PRIVATE_KEY);
    return script;
}

void destroy_admin_script(AdminScript *script) {
    free(script->admin_name);
    free(script->private_key);
    free(script);
}

int main() {
    AdminScript *script = create_admin_script("admin_user");
    printf("Admin Script created with private key: %s\n", script->private_key);
    destroy_admin_script(script);
    return 0;
}