#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* sender;
    char* message;
} Message;

void process_message(Message* msg, const char* body) {
    char* token = strtok((char*)body, "|");
    msg->sender = strdup(token);
    token = strtok(NULL, "|");
    msg->message = strdup(token);
}

int main() {
    const char* body = "john_doe|Hello, World!";
    Message msg;
    process_message(&msg, body);
    printf("Sender: %s, Message: %s\n", msg.sender, msg.message);
    free(msg.sender);
    free(msg.message);
    return 0;
}