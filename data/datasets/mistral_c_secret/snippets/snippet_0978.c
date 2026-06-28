#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY_ENV_VAR "PRIVATE_KEY"

typedef struct {
    char *admin_server;
    int admin_port;
    char *private_key;
} AdminScript;

AdminScript* create_admin_script(const char *admin_server, int admin_port) {
    AdminScript *script = (AdminScript*)malloc(sizeof(AdminScript));
    if (script == NULL) {
        return NULL;
    }

    script->admin_server = strdup(admin_server);
    script->admin_port = admin_port;

    if (script->admin_server == NULL) {
        free(script);
        return NULL;
    }

    const char *key = getenv(PRIVATE_KEY_ENV_VAR);
    if (key == NULL) {
        fprintf(stderr, "Error: Private key not found in environment variables.\n");
        free(script->admin_server);
        free(script);
        return NULL;
    }

    script->private_key = strdup(key);
    if (script->private_key == NULL) {
        free(script->admin_server);
        free(script);
        return NULL;
    }

    return script;
}

void destroy_admin_script(AdminScript *script) {
    if (script != NULL) {
        free(script->admin_server);
        free(script->private_key);
        free(script);
    }
}

int main() {
    AdminScript *script = create_admin_script("admin.example.com", 9090);
    if (script == NULL) {
        return EXIT_FAILURE;
    }

    printf("Admin script created.\n");
    printf("Admin Server: %s\n", script->admin_server);
    printf("Admin Port: %d\n", script->admin_port);

    destroy_admin_script(script);
    return EXIT_SUCCESS;
}