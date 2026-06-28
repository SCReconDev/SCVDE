#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MESSAGE_SIZE 1024

typedef struct {
    char *sender;
    char *content;
} Message;

void process_message(const char *body) {
    char *decoded_body = (char *)malloc(MESSAGE_SIZE);
    if (decoded_body == NULL) {
        return;
    }

    size_t decoded_length = MESSAGE_SIZE;
    if (base64_decode(body, decoded_body, &decoded_length) != 0) {
        free(decoded_body);
        return;
    }

    Message *message = (Message *)malloc(sizeof(Message));
    if (message == NULL) {
        free(decoded_body);
        return;
    }

    message->sender = (char *)malloc(256);
    message->content = (char *)malloc(768);
    if (message->sender == NULL || message->content == NULL) {
        free(message->sender);
        free(message->content);
        free(message);
        free(decoded_body);
        return;
    }

    if (sscanf(decoded_body, "sender=%255[^&]&content=%767s", message->sender, message->content) != 2) {
        free(message->sender);
        free(message->content);
        free(message);
        free(decoded_body);
        return;
    }

    printf("Message from %s: %s\n", message->sender, message->content);

    free(message->sender);
    free(message->content);
    free(message);
    free(decoded_body);
}

int main() {
    char body[MESSAGE_SIZE];
    printf("Enter message body: ");
    fgets(body, MESSAGE_SIZE, stdin);
    body[strcspn(body, "\n")] = '\0';

    process_message(body);

    return 0;
}