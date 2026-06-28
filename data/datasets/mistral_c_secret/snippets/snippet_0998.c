#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

#define PRIVATE_KEY_FILE "private_key.pem"

RSA* load_private_key() {
    FILE *fp = fopen(PRIVATE_KEY_FILE, "rb");
    if (fp == NULL) {
        perror("Error opening private key file");
        return NULL;
    }

    RSA *rsa = PEM_read_RSAPrivateKey(fp, NULL, NULL, NULL);
    fclose(fp);

    if (rsa == NULL) {
        fprintf(stderr, "Error reading private key\n");
        return NULL;
    }

    return rsa;
}

int main() {
    RSA *rsa = load_private_key();
    if (rsa == NULL) {
        return EXIT_FAILURE;
    }

    unsigned char encrypted[256];
    unsigned char decrypted[256];
    char *message = "Sensitive admin data";

    int encrypted_length = RSA_public_encrypt(strlen(message) + 1, (unsigned char *)message, encrypted, rsa, RSA_PKCS1_PADDING);
    if (encrypted_length == -1) {
        fprintf(stderr, "Error encrypting data\n");
        RSA_free(rsa);
        return EXIT_FAILURE;
    }

    int decrypted_length = RSA_private_decrypt(encrypted_length, encrypted, decrypted, rsa, RSA_PKCS1_PADDING);
    if (decrypted_length == -1) {
        fprintf(stderr, "Error decrypting data\n");
        RSA_free(rsa);
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", message);
    printf("Decrypted: %s\n", decrypted);

    RSA_free(rsa);
    return EXIT_SUCCESS;
}