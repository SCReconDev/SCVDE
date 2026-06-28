#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *private_key;
    char *admin_email;
} AdminScript;

AdminScript* create_admin_script(const char *admin_email) {
    AdminScript *script = (AdminScript*)malloc(sizeof(AdminScript));
    if (script == NULL) {
        return NULL;
    }
    script->admin_email = strdup(admin_email);
    script->private_key = getenv("ADMIN_PRIVATE_KEY");
    if (script->private_key == NULL) {
        fprintf(stderr, "ADMIN_PRIVATE_KEY environment variable not set\n");
        free(script->admin_email);
        free(script);
        return NULL;
    }
    return script;
}

void destroy_admin_script(AdminScript *script) {
    if (script != NULL) {
        free(script->admin_email);
        free(script);
    }
}

void execute_admin_task(AdminScript *script, const char *task) {
    printf("Executing admin task: %s\n", task);
    printf("Admin email: %s\n", script->admin_email);
    printf("Private key: %s\n", script->private_key);
}

int main() {
    AdminScript *script = create_admin_script("admin@example.com");
    if (script == NULL) {
        return 1;
    }

    execute_admin_task(script, "Backup database");

    destroy_admin_script(script);
    return 0;
}