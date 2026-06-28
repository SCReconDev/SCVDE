#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

#define SECRET_KEY_SIZE 32

int main() {
    char *secret_key = getenv("PAYMENT_SECRET_KEY");

    if(secret_key == NULL) {
        fprintf(stderr, "PAYMENT_SECRET_KEY environment variable not set\n");
        return EXIT_FAILURE;
    }

    if(strlen(secret_key) != SECRET_KEY_SIZE) {
        fprintf(stderr, "Invalid secret key size\n");
        return EXIT_FAILURE;
    }

    unsigned char encrypted_data[128];
    unsigned char iv[EVP_MAX_IV_LENGTH];

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (unsigned char *)secret_key, iv);

    char *data_to_encrypt = "Sensitive payment data";
    int len = strlen(data_to_encrypt);
    int ciphertext_len;

    EVP_EncryptUpdate(ctx, encrypted_data, &ciphertext_len, (unsigned char *)data_to_encrypt, len);

    int final_len;
    EVP_EncryptFinal_ex(ctx, encrypted_data + ciphertext_len, &final_len);

    EVP_CIPHER_CTX_free(ctx);

    printf("Encrypted data: ");
    for(int i = 0; i < ciphertext_len + final_len; i++) {
        printf("%02x", encrypted_data[i]);
    }
    printf("\n");

    return 0;
}