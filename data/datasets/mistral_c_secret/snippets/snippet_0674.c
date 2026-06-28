#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    char *secret_key;
    char *api_url;
} PaymentGatewayConfig;

PaymentGatewayConfig* create_payment_gateway_config() {
    PaymentGatewayConfig *config = (PaymentGatewayConfig*)malloc(sizeof(PaymentGatewayConfig));
    config->secret_key = getenv("PAYMENT_SECRET_KEY");
    config->api_url = getenv("PAYMENT_API_URL");

    if (config->secret_key == NULL || config->api_url == NULL) {
        fprintf(stderr, "PAYMENT_SECRET_KEY and PAYMENT_API_URL environment variables must be set.\n");
        free(config);
        return NULL;
    }

    return config;
}

void destroy_payment_gateway_config(PaymentGatewayConfig *config) {
    if (config != NULL) {
        free(config);
    }
}

int main() {
    PaymentGatewayConfig *config = create_payment_gateway_config();
    if (config == NULL) {
        return EXIT_FAILURE;
    }

    CURL *curl = curl_easy_init();
    if (curl) {
        struct curl_slist *headers = NULL;
        char auth_header[256];
        snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", config->secret_key);
        headers = curl_slist_append(headers, auth_header);

        curl_easy_setopt(curl, CURLOPT_URL, config->api_url);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    destroy_payment_gateway_config(config);
    return EXIT_SUCCESS;
}