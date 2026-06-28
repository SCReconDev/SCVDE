#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    char* username;
    char* password;
} User;

size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
    char **response_ptr = (char **)userdata;
    *response_ptr = strndup(ptr, size * nmemb);
    return size * nmemb;
}

User* deserialize_user(const char* data) {
    User* user = malloc(sizeof(User));
    char* token = strtok((char*)data, ":");
    user->username = strdup(token);
    token = strtok(NULL, ":");
    user->password = strdup(token);
    return user;
}

void handle_request(const char* url) {
    CURL *curl = curl_easy_init();
    if(curl) {
        char* response = NULL;
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        CURLcode res = curl_easy_perform(curl);
        if(res == CURLE_OK) {
            User* user = deserialize_user(response);
            printf("User: %s\n", user->username);
            free(user->username);
            free(user->password);
            free(user);
        }
        free(response);
        curl_easy_cleanup(curl);
    }
}

int main() {
    handle_request("http://example.com/api/user");
    return 0;
}