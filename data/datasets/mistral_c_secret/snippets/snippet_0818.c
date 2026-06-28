#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *private_key;
    char *admin_name;
} AdminScript;

AdminScript* create_admin_script(const char *admin_name) {
    AdminScript *script = (AdminScript*)malloc(sizeof(AdminScript));
    script->admin_name = strdup(admin_name);
    script->private_key = getenv("ADMIN_PRIVATE_KEY");
    if (script->private_key == NULL) {
        fprintf(stderr, "ADMIN_PRIVATE_KEY environment variable not set\n");
        free(script->admin_name);
        free(script);
        return NULL;
    }
    return script;
}

void destroy_admin_script(AdminScript *script) {
    if (script != NULL) {
        free(script->admin_name);
        free(script);
    }
}

int main() {
    AdminScript *script = create_admin_script("admin_user");
    if (script == NULL) {
        return 1;
    }
    printf("Admin script created for admin: %s\n", script->admin_name);
    destroy_admin_script(script);
    return 0;
}