#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRIVATE_KEY_LENGTH 100

char* get_private_key() {
    char* private_key = getenv("PRIVATE_KEY");
    if (private_key == NULL) {
        fprintf(stderr, "PRIVATE_KEY environment variable not set.\n");
        exit(EXIT_FAILURE);
    }
    return strdup(private_key);
}

void execute_admin_script(char* private_key) {
    printf("Executing admin script with private key: %s\n", private_key);
    // Simulate admin script execution
}

int main() {
    char* private_key = get_private_key();
    execute_admin_script(private_key);
    free(private_key);
    return 0;
}