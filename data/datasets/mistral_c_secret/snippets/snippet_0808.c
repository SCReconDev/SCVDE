#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRIVATE_KEY_LENGTH 100

typedef struct {
    char private_key[MAX_PRIVATE_KEY_LENGTH];
} AdminScript;

AdminScript* create_admin_script() {
    AdminScript* script = (AdminScript*)malloc(sizeof(AdminScript));
    if (script == NULL) {
        return NULL;
    }

    const char* private_key_env = getenv("ADMIN_PRIVATE_KEY");
    if (private_key_env == NULL) {
        fprintf(stderr, "ADMIN_PRIVATE_KEY environment variable not set\n");
        free(script);
        return NULL;
    }

    strncpy(script->private_key, private_key_env, MAX_PRIVATE_KEY_LENGTH - 1);
    script->private_key[MAX_PRIVATE_KEY_LENGTH - 1] = '\0';

    return script;
}

void execute_admin_task(AdminScript* script, const char* task) {
    printf("Executing admin task %s with private key: %s\n", task, script->private_key);
}

void destroy_admin_script(AdminScript* script) {
    if (script != NULL) {
        free(script);
    }
}

int main() {
    AdminScript* script = create_admin_script();
    if (script == NULL) {
        return 1;
    }

    execute_admin_task(script, "task_name");
    destroy_admin_script(script);

    return 0;
}