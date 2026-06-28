#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* sender;
    char* message;
} Message;

void process_message(const char* body) {
    Message* msg = (Message*)malloc(sizeof(Message));
    memcpy(msg, body, sizeof(Message));

    printf("Message from %s: %s\n", msg->sender, msg->message);
    free(msg);
}

int main() {
    char* message_body = "Bob\0Hello, World!";
    process_message(message_body);
    return 0;
}