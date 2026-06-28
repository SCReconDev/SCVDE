#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY "fake_private_key_1234567890"

typedef struct {
    char *admin_id;
    char *private_key;
} AdminScript;

AdminScript* create_admin_script(const char *admin_id) {
    AdminScript *script = (AdminScript*)malloc(sizeof(AdminScript));
    script->admin_id = strdup(admin_id);
    script->private_key = strdup(PRIVATE_KEY);
    return script;
}

void execute_admin_task(AdminScript *script, const char *task) {
    printf("Executing admin task %s for admin %s with private key %s\n", task, script->admin_id, script->private_key);
}

void destroy_admin_script(AdminScript *script) {
    free(script->admin_id);
    free(script->private_key);
    free(script);
}

int main() {
    AdminScript *script = create_admin_script("admin_1234567890");
    execute_admin_task(script, "backup_database");
    destroy_admin_script(script);
    return 0;
}