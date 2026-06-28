#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *admin_user;
    char *private_key;
} AdminScript;

AdminScript* create_admin_script(const char *admin_user) {
    AdminScript *script = (AdminScript*)malloc(sizeof(AdminScript));
    if (script == NULL) {
        return NULL;
    }

    script->admin_user = strdup(admin_user);
    if (script->admin_user == NULL) {
        free(script);
        return NULL;
    }

    script->private_key = getenv("ADMIN_PRIVATE_KEY");
    if (script->private_key == NULL) {
        fprintf(stderr, "ADMIN_PRIVATE_KEY environment variable not set.\n");
        free(script->admin_user);
        free(script);
        return NULL;
    }

    return script;
}

void destroy_admin_script(AdminScript *script) {
    if (script != NULL) {
        if (script->admin_user != NULL) {
            free(script->admin_user);
        }
        free(script);
    }
}

int execute_admin_command(AdminScript *script, const char *command) {
    if (script == NULL || command == NULL) {
        return -1;
    }

    // Simulate executing an admin command
    printf("Executing admin command: %s\n", command);
    printf("Admin user: %s\n", script->admin_user);
    printf("Private key: %s\n", script->private_key);

    return 0;
}