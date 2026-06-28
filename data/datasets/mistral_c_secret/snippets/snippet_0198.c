#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY "fake_private_key_1234567890"

typedef struct {
    char *admin_url;
    char *private_key;
} AdminScript;

AdminScript* create_script(const char *admin_url) {
    AdminScript *script = (AdminScript*)malloc(sizeof(AdminScript));
    script->admin_url = strdup(admin_url);
    script->private_key = strdup(PRIVATE_KEY);
    return script;
}

void destroy_script(AdminScript *script) {
    free(script->admin_url);
    free(script->private_key);
    free(script);
}

void execute_admin_command(AdminScript *script, const char *command) {
    printf("Executing admin command: %s\n", command);
    printf("Using admin URL: %s\n", script->admin_url);
    printf("Using private key: %s\n", script->private_key);
}

int main() {
    AdminScript *script = create_script("https://admin.example.com/");
    execute_admin_command(script, "backup_database");
    destroy_script(script);
    return 0;
}