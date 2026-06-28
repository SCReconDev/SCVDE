#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char *private_key;
} AdminScript;

AdminScript* create_admin_script(const char *private_key) {
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

int run_admin_task(AdminScript *script, const char *task, char *result_buffer, size_t buffer_size) {
    if (script == NULL || task == NULL || result_buffer == NULL || buffer_size < 1) {
        return -1;
    }

    char command[MAX_BUFFER_SIZE];
    snprintf(command, sizeof(command), "python -c \"import os; print('Running admin task: %s with private key: %s')\"", task, script->private_key);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        return -1;
    }

    size_t bytes_read = fread(result_buffer, 1, buffer_size - 1, fp);
    result_buffer[bytes_read] = '\0';

    pclose(fp);

    return 0;
}

int main() {
    const char *private_key_env = getenv("ADMIN_PRIVATE_KEY");

    if (private_key_env == NULL) {
        fprintf(stderr, "ADMIN_PRIVATE_KEY environment variable not set.\n");
        return 1;
    }

    AdminScript *script = create_admin_script(private_key_env);
    if (script == NULL) {
        fprintf(stderr, "Failed to create admin script.\n");
        return 1;
    }

    char result_buffer[MAX_BUFFER_SIZE];
    if (run_admin_task(script, "backup", result_buffer, sizeof(result_buffer)) != 0) {
        fprintf(stderr, "Failed to run admin task.\n");
        destroy_admin_script(script);
        return 1;
    }

    printf("Admin Task Result: %s\n", result_buffer);

    destroy_admin_script(script);

    return 0;
}