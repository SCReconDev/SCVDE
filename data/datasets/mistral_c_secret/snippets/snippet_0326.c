#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

#define BEARER_TOKEN "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ.SflKxwRJSMeKKF2QT4fwpMeJf36POk6yJV_adQssw5c"

void call_third_party_api() {
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl) {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Authorization: Bearer " BEARER_TOKEN);

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.thirdparty.com/data");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
}

int main() {
    call_third_party_api();
    return 0;
}