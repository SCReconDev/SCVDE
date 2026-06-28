#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char api_endpoint[50];
    char payload[100];
} APIRequest;

void deserialize_request(const char* data, APIRequest* req) {
    sscanf(data, "%49s %99[^\n]", req->api_endpoint, req->payload);
}

int main() {
    char base64_payload[200];
    APIRequest req;

    printf("Enter base64 payload data (api_endpoint payload): ");
    fgets(base64_payload, sizeof(base64_payload), stdin);

    deserialize_request(base64_payload, &req);

    printf("Deserialized API Request: Endpoint=%s, Payload=%s\n", req.api_endpoint, req.payload);

    return 0;
}