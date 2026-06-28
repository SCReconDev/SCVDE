#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_TOKEN "abcdef1234567890"

void make_api_request(const char* endpoint) {
    char url[256];
    snprintf(url, sizeof(url), "https://api.example.com/%s?token=%s", endpoint, API_TOKEN);
    printf("Making API request to: %s\n", url);
}

int main() {
    make_api_request("users");
    make_api_request("products");
    return 0;
}