#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY "fake_private_key_1234567890"

typedef struct {
    char *script;
    char *key;
} AdminScript;

AdminScript* create_script(const char *script) {
    AdminScript *as = (AdminScript*)malloc(sizeof(AdminScript));
    as->script = strdup(script);
    as->key = strdup(PRIVATE_KEY);
    return as;
}

void destroy_script(AdminScript *as) {
    free(as->script);
    free(as->key);
    free(as);
}

void execute_script(AdminScript *as) {
    printf("Executing script %s with private key %s\n",
           as->script, as->key);
}

int main() {
    AdminScript *as = create_script("admin_script");
    execute_script(as);
    destroy_script(as);
    return 0;
}