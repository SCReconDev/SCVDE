#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY "fake_private_key_24680"

int main() {
    char admin_script[256];
    snprintf(admin_script, sizeof(admin_script), "AdminScript: %s", PRIVATE_KEY);

    printf("Admin script: %s\n", admin_script);

    return 0;
}