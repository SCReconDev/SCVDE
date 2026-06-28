#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* sender;
    char* message;
} Message;

void process_message(const char* body, Message* msg) {
    char* data = strdup(body);
    char* token = strtok(data, ",");
    msg->sender = strdup(token);
    token = strtok(NULL, ",");
    msg->message = strdup(token);
    free(data);
}

int main() {
    char* message_body = "user123,Hello, World!";
    Message msg;
    process_message(message_body, &msg);
    printf("Sender: %s, Message: %s\n", msg.sender, msg.message);
    free(msg.sender);
    free(msg.message);
    return 0;
}