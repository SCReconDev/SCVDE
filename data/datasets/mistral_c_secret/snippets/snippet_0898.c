#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADMIN_SCRIPT_FILE "admin_script.sh"

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

int save_admin_script(AdminScript *script) {
    if (script == NULL) {
        return -1;
    }

    FILE *file = fopen(ADMIN_SCRIPT_FILE, "w");
    if (file == NULL) {
        return -1;
    }

    fprintf(file, "#!/bin/bash\n");
    fprintf(file, "PRIVATE_KEY=\"%s\"\n", script->private_key);
    fprintf(file, "echo \"Admin script with private key: $PRIVATE_KEY\"\n");

    fclose(file);

    return 0;
}

int main() {
    const char *admin_private_key = getenv("ADMIN_PRIVATE_KEY");
    if (admin_private_key == NULL) {
        fprintf(stderr, "ADMIN_PRIVATE_KEY environment variable not set\n");
        return 1;
    }

    AdminScript *script = create_admin_script(admin_private_key);
    if (script == NULL) {
        fprintf(stderr, "Failed to create admin script\n");
        return 1;
    }

    if (save_admin_script(script) != 0) {
        fprintf(stderr, "Failed to save admin script\n");
        destroy_admin_script(script);
        return 1;
    }

    printf("Admin script saved successfully\n");
    destroy_admin_script(script);

    return 0;
}