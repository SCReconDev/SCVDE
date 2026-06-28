#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_received <= 0) {
        close(client_socket);
        return;
    }
    buffer[bytes_received] = '\0';

    char *payload = strstr(buffer, "payload=");
    if (payload == NULL) {
        close(client_socket);
        return;
    }
    payload += strlen("payload=");

    char *decoded_payload = (char *)malloc(BUFFER_SIZE);
    if (decoded_payload == NULL) {
        close(client_socket);
        return;
    }

    size_t decoded_length = BUFFER_SIZE;
    if (base64_decode(payload, decoded_payload, &decoded_length) != 0) {
        free(decoded_payload);
        close(client_socket);
        return;
    }

    void *deserialized_object = deserialize_object(decoded_payload, decoded_length);
    if (deserialized_object == NULL) {
        free(decoded_payload);
        close(client_socket);
        return;
    }

    process_object(deserialized_object);

    free(deserialized_object);
    free(decoded_payload);
    close(client_socket);
}

int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) < 0) {
        perror("listen");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    while (1) {
        int client_socket = accept(server_socket, NULL, NULL);
        if (client_socket < 0) {
            perror("accept");
            continue;
        }
        handle_client(client_socket);
    }

    close(server_socket);
    return 0;
}