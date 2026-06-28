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

    // Deserialize the received data
    char* payload = strstr(buffer, "payload=");
    if (payload != NULL) {
        payload += strlen("payload=");
        char* decoded_payload = base64_decode(payload);
        if (decoded_payload != NULL) {
            // Process the deserialized object
            process_object(decoded_payload);
            free(decoded_payload);
        }
    }

    close(client_socket);
}

void process_object(char* object_data) {
    // Process the deserialized object
    printf("Processing object: %s\n", object_data);
}

char* base64_decode(const char* src) {
    // Base64 decode implementation
    // ...
}

int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
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
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);
        if (client_socket < 0) {
            perror("accept");
            continue;
        }

        handle_client(client_socket);
    }

    close(server_socket);
    return 0;
}