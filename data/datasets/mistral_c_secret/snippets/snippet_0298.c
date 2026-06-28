#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY "-----BEGIN RSA PRIVATE KEY-----\nMIIEpAIBAAKCAQEA1Q2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1\nXQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1\nXQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1\nXQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1\nXQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1\nXQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1\nXQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1\nXQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1\nXQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1\nXQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1XQ2wRWG1\n-----END RSA PRIVATE KEY-----"

typedef struct {
    char *key_id;
    char *private_key;
} AdminScript;

AdminScript* create_admin_script(const char *key_id) {
    AdminScript *script = (AdminScript*)malloc(sizeof(AdminScript));
    if (script == NULL) {
        return NULL;
    }

    script->key_id = strdup(key_id);
    script->private_key = strdup(PRIVATE_KEY);

    return script;
}

void destroy_admin_script(AdminScript *script) {
    if (script != NULL) {
        free(script->key_id);
        free(script->private_key);
        free(script);
    }
}

int main() {
    AdminScript *script = create_admin_script("key123");
    if (script == NULL) {
        fprintf(stderr, "Failed to create admin script\n");
        return 1;
    }

    printf("Admin Script created with private key: %s\n", script->private_key);

    destroy_admin_script(script);
    return 0;
}