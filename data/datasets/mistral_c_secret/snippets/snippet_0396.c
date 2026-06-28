#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BEARER_TOKEN "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ.SflKxwRJSMeKKF2QT4fwpMeJf36POk6yJV_adQssw5c"

void fetch_third_party_data() {
    char api_url[256];
    snprintf(api_url, sizeof(api_url), "https://api.thirdparty.com/data?token=%s", BEARER_TOKEN);
    // Simulate fetching data from the third-party API
    printf("Fetching data from: %s\n", api_url);
}

int main() {
    fetch_third_party_data();
    return 0;
}