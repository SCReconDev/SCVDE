#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* sender;
    char* message;
} Message;

void deserialize_message(char* data, Message* msg) {
    char* token = strtok(data, ";");
    msg->sender = strdup(token);
    token = strtok(NULL, ";");
    msg->message = strdup(token);
}

void process_message(char* body) {
    Message msg;
    deserialize_message(body, &msg);
    printf("Sender: %s, Message: %s\n", msg.sender, msg.message);
    free(msg.sender);
    free(msg.message);
}

int main() {
    char* body = "john_doe;Hello, World!";
    process_message(body);
    return 0;
}