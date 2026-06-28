#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define API_URL "https://api.example.com/auth"

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if(!ptr) {
        printf("Not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

int main(void) {
    CURL *curl;
    CURLcode res;
    struct MemoryStruct chunk;

    chunk.memory = malloc(1);
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if(curl) {
        char *client_secret = getenv("OAUTH_CLIENT_SECRET");
        if(client_secret == NULL) {
            fprintf(stderr, "OAUTH_CLIENT_SECRET environment variable not set\n");
            return EXIT_FAILURE;
        }

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");

        char post_data[512];
        snprintf(post_data, sizeof(post_data), "client_id=your_client_id&client_secret=%s&grant_type=client_credentials", client_secret);

        curl_easy_setopt(curl, CURLOPT_URL, API_URL);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            printf("%s\n", chunk.memory);
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    free(chunk.memory);
    curl_global_cleanup();

    return 0;
}