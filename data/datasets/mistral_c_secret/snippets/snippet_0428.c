#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY "fake_private_key_1234567890"

int main() {
    char user[64] = "admin";
    char command[512];

    snprintf(command, sizeof(command), "ssh -i %s %s@server.example.com", PRIVATE_KEY, user);

    system(command);

    return 0;
}