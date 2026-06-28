#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* sender;
    char* message;
} Message;

void process_message(Message* msg, const char* data) {
    char* token = strtok((char*)data, ";");
    msg->sender = strdup(token);
    token = strtok(NULL, ";");
    msg->message = strdup(token);
}

int main() {
    char* msg_data = "user1;Hello, world!";
    Message msg;
    process_message(&msg, msg_data);
    printf("Sender: %s, Message: %s\n", msg.sender, msg.message);
    free(msg.sender);
    free(msg.message);
    return 0;
}