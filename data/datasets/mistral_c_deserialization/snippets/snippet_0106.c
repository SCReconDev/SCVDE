#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* sender;
    char* message;
} Message;

void process_message(Message* msg, const char* body) {
    char* token = strdup(body);
    char* part = strtok(token, "|");
    msg->sender = strdup(part);
    part = strtok(NULL, "|");
    msg->message = strdup(part);
    free(token);
}

int main() {
    char* body = "user123|Hello, world!";
    Message msg;
    process_message(&msg, body);
    printf("Sender: %s, Message: %s\n", msg.sender, msg.message);
    return 0;
}