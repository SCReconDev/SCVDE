#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *script_name;
    char *private_key;
} AdminScript;

AdminScript *create_admin_script(const char *script_name, const char *env_var) {
    AdminScript *script = (AdminScript *)malloc(sizeof(AdminScript));
    script->script_name = strdup(script_name);
    script->private_key = getenv(env_var);
    if (script->private_key == NULL) {
        fprintf(stderr, "Error: Environment variable not set\n");
        exit(EXIT_FAILURE);
    }
    return script;
}

void destroy_admin_script(AdminScript *script) {
    free(script->script_name);
    free(script);
}

int main() {
    const char *script_name = "Admin Script";
    const char *env_var = "PRIVATE_KEY";
    AdminScript *script = create_admin_script(script_name, env_var);
    printf("Admin Script created with name: %s\n", script->script_name);
    destroy_admin_script(script);
    return 0;
}