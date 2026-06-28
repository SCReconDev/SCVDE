#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY_FILE "private_key.pem"

typedef struct {
    char *private_key;
} AdminScript;

AdminScript *create_admin_script(const char *private_key) {
    AdminScript *script = (AdminScript *)malloc(sizeof(AdminScript));
    if (script == NULL) {
        return NULL;
    }

    script->private_key = strdup(private_key);
    if (script->private_key == NULL) {
        free(script);
        return NULL;
    }

    return script;
}

void destroy_admin_script(AdminScript *script) {
    if (script != NULL) {
        free(script->private_key);
        free(script);
    }
}

int save_private_key(AdminScript *script) {
    if (script == NULL || script->private_key == NULL) {
        return -1;
    }

    FILE *file = fopen(PRIVATE_KEY_FILE, "w");
    if (file == NULL) {
        fprintf(stderr, "Failed to open private key file for writing.\n");
        return -1;
    }

    fprintf(file, "%s\n", script->private_key);

    fclose(file);

    printf("Successfully saved private key.\n");

    return 0;
}

int main() {
    const char *private_key = getenv("PRIVATE_KEY");
    if (private_key == NULL) {
        fprintf(stderr, "PRIVATE_KEY environment variable not set.\n");
        return 1;
    }

    AdminScript *script = create_admin_script(private_key);
    if (script == NULL) {
        fprintf(stderr, "Failed to create admin script.\n");
        return 1;
    }

    if (save_private_key(script) != 0) {
        destroy_admin_script(script);
        return 1;
    }

    destroy_admin_script(script);

    return 0;
}