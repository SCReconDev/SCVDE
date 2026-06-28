#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY "fake_secret_key_1234567890"

int main() {
    char payment_id[64] = "payment_1234567890";
    char amount[16] = "100.00";
    char command[512];

    snprintf(command, sizeof(command), "curl -X POST https://api.paymentgateway.com/charge -H \"Content-Type: application/json\" -d \"{\\\"payment_id\\\":\\\"%s\\\",\\\"amount\\\":\\\"%s\\\",\\\"secret_key\\\":\\\"%s\\\"}\"", payment_id, amount, SECRET_KEY);

    system(command);

    return 0;
}