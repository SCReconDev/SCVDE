#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECRET_KEY "fake_secret_key_fghij"

int main() {
    char payment_request[256];
    char payment_response[1024];

    snprintf(payment_request, sizeof(payment_request), "https://payment.example.com/process?key=%s", SECRET_KEY);

    // Simulate payment request
    printf("Making payment request to: %s\n", payment_request);

    // Simulate payment response
    snprintf(payment_response, sizeof(payment_response), "{\"status\": \"success\", \"transaction_id\": \"12345\"}");
    printf("Payment Response: %s\n", payment_response);

    return 0;
}