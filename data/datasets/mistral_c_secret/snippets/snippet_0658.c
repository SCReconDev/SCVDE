#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADMIN_PRIVATE_KEY_ENV_VAR "ADMIN_PRIVATE_KEY"

typedef struct {
    char *admin_url;
    char *private_key;
} AdminScript;

AdminScript *create_admin_script(const char *admin_url) {
    AdminScript *script = (AdminScript *)malloc(sizeof(AdminScript));
    if (script == NULL) {
        return NULL;
    }

    script->admin_url = strdup(admin_url);
    if (script->admin_url == NULL) {
        free(script);
        return NULL;
    }

    script->private_key = getenv(ADMIN_PRIVATE_KEY_ENV_VAR);
    if (script->private_key == NULL) {
        fprintf(stderr, "Admin private key not found in environment variables\n");
        free(script->admin_url);
        free(script);
        return NULL;
    }

    return script;
}

void destroy_admin_script(AdminScript *script) {
    if (script != NULL) {
        if (script->admin_url != NULL) {
            free(script->admin_url);
        }
        free(script);
    }
}

int main() {
    const char *admin_url = "https://admin.example.com";

    AdminScript *script = create_admin_script(admin_url);

    if (script != NULL) {
        printf("Admin script created successfully\n");
        destroy_admin_script(script);
    } else {
        fprintf(stderr, "Failed to create admin script\n");
    }

    return 0;
}