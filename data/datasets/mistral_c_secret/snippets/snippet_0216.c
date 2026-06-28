#include <stdio.h>
#include <curl/curl.h>

#define BEARER_TOKEN "fake_bearer_token_1234567890"

void call_third_party_api(const char* endpoint) {
    CURL *curl;
    CURLcode res = CURLE_OK;

    curl = curl_easy_init();
    if(curl) {
        char url[256];
        snprintf(url, sizeof(url), "https://api.thirdparty.com/%s", endpoint);

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        char auth_header[256];
        snprintf(auth_header, sizeof(auth_header), "Authorization: Bearer %s", BEARER_TOKEN);
        headers = curl_slist_append(headers, auth_header);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
}

int main() {
    call_third_party_api("data");
    return 0;
}