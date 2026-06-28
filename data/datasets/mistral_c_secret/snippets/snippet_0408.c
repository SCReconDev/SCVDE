#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRIVATE_KEY "-----BEGIN PRIVATE KEY-----\nMIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQC7VJTUt9Us8cKj\n9yboX7N2w7XO5j/D1S0X/k5mXUtk6+L8Z4ATndZnXoASzKJR4sOBCVmePMBPrCHt\nRujV/GG1qyPLTk0x4xnWfIFPUD6LkFDovK7grLHY4w0GLbzyPLhWqanSuvz9Jgk/\n6JGhBqGVG3wSS8W2PHuSY6grJVdQOH3WN1DVv+3Y0hPMbckxHkmbPW2SXhEdPK/2\ny0IEtmcmPFjYW9IqNtPZyeIbtOwrR10csV8AevFSBX6sMhCQvFy8ZLYizJ+ynKTp\n9z0xLQTpNq8j1LpHj0KR921p2uzD1c0H5k9HUa0bHJ0QZQJdZQJdZQJdZQJdZQJd\n-----END PRIVATE KEY-----\n"

void admin_function() {
    printf("Executing admin function with private key: %s\n", PRIVATE_KEY);
}

int main() {
    admin_function();
    return 0;
}