#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY "-----BEGIN PRIVATE KEY-----\nMIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQC7b\n...\n-----END PRIVATE KEY-----\n"

typedef struct {
    char *service_url;
    char *private_key;
} AdminScript;

AdminScript *create_script(const char *service_url) {
    AdminScript *script = (AdminScript *)malloc(sizeof(AdminScript));
    script->service_url = strdup(service_url);
    script->private_key = strdup(PRIVATE_KEY);
    return script;
}

void destroy_script(AdminScript *script) {
    free(script->service_url);
    free(script->private_key);
    free(script);
}

void execute_script(AdminScript *script) {
    printf("Executing script on service: %s with private key: %s\n", script->service_url, script->private_key);
}

int main() {
    AdminScript *script = create_script("https://admin.example.com/service");
    execute_script(script);
    destroy_script(script);
    return 0;
}