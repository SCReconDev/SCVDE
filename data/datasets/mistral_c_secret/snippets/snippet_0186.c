#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define BEARER_TOKEN "fake_bearer_token_1234567890"

int make_third_party_request(const char* endpoint) {
    CURL *curl;
    CURLcode res = CURLE_OK;

    curl = curl_easy_init();
    if(curl) {
        char url[256];
        snprintf(url, sizeof(url), "https://thirdparty.example.com/%s", endpoint);

        curl_easy_setopt(curl, CURLOPT_URL, url);

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Authorization: Bearer " BEARER_TOKEN);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    return (int)res;
}

int main() {
    make_third_party_request("users");
    make_third_party_request("products");

    return 0;
}