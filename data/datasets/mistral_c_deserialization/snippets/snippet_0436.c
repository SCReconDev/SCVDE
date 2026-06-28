#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* sender;
    char* message;
} Message;

void process_message(Message* msg) {
    printf("Message from %s: %s\n", msg->sender, msg->message);
}

int main() {
    char* message_body = "{\"sender\":\"user1\",\"message\":\"Hello, world!\"}";
    Message* msg = (Message*)malloc(sizeof(Message));
    memcpy(msg, message_body, sizeof(Message));
    process_message(msg);
    free(msg);
    return 0;
}