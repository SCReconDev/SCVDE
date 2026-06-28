#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* sender;
    char* message;
} Message;

void load_message(const char* body, Message* msg) {
    char* token = strtok((char*)body, "|");
    msg->sender = strdup(token);
    token = strtok(NULL, "|");
    msg->message = strdup(token);
}

void process_message(const char* message_body) {
    Message msg;
    load_message(message_body, &msg);
    printf("Sender: %s, Message: %s\n", msg.sender, msg.message);
    free(msg.sender);
    free(msg.message);
}

int main() {
    const char* message_body = "john_doe|Hello, world!";
    process_message(message_body);
    return 0;
}