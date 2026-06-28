#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY "fake_secret_key_1234567890"

int main() {
    char card_number[16] = "4111111111111111";
    char expiry_date[5] = "1225";
    char cvv[3] = "123";

    char payment_data[256];
    snprintf(payment_data, sizeof(payment_data), "card_number=%s&expiry_date=%s&cvv=%s&secret_key=%s",
             card_number, expiry_date, cvv, SECRET_KEY);

    char command[512];
    snprintf(command, sizeof(command), "curl -X POST -d '%s' https://payment.example.com/process", payment_data);

    FILE *pipe = popen(command, "r");
    if (!pipe) {
        perror("Failed to run command");
        return 1;
    }

    char response[1024];
    while (fgets(response, sizeof(response), pipe) != NULL) {
        printf("%s", response);
    }

    pclose(pipe);
    return 0;
}