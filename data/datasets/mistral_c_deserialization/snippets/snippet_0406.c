#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* sender;
    char* message;
} Message;

void process_message(const char* body, Message* msg) {
    char* token = strtok((char*)body, ";");
    msg->sender = strdup(token);
    token = strtok(NULL, ";");
    msg->message = strdup(token);
}

int main() {
    char* message_body = "John Doe;Hello, world!";
    Message msg;
    process_message(message_body, &msg);
    printf("Sender: %s, Message: %s\n", msg.sender, msg.message);
    free(msg.sender);
    free(msg.message);
    return 0;
}