#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADMIN_SCRIPT_URL "https://admin.example.com/v1"
#define PRIVATE_KEY_ENV "PRIVATE_KEY"

typedef struct {
    char *url;
    char *private_key;
} AdminScript;

AdminScript *create_admin_script() {
    AdminScript *script = (AdminScript *)malloc(sizeof(AdminScript));
    if (script == NULL) {
        return NULL;
    }

    script->url = strdup(ADMIN_SCRIPT_URL);
    if (script->url == NULL) {
        free(script);
        return NULL;
    }

    char *private_key = getenv(PRIVATE_KEY_ENV);
    if (private_key == NULL) {
        free(script->url);
        free(script);
        return NULL;
    }

    script->private_key = strdup(private_key);
    if (script->private_key == NULL) {
        free(script->url);
        free(script);
        return NULL;
    }

    return script;
}

void destroy_admin_script(AdminScript *script) {
    if (script != NULL) {
        free(script->url);
        free(script->private_key);
        free(script);
    }
}

int main() {
    AdminScript *script = create_admin_script();
    if (script == NULL) {
        fprintf(stderr, "Failed to create admin script\n");
        return 1;
    }

    printf("Admin Script created with URL: %s and Private Key: %s\n", script->url, script->private_key);

    destroy_admin_script(script);
    return 0;
}