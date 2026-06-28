#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char sender[50];
    char message[100];
} Message;

void process_message(const char* body, Message* msg) {
    char* data = strdup(body);
    char* token = strtok(data, "|");
    strcpy(msg->sender, token);
    token = strtok(NULL, "|");
    strcpy(msg->message, token);
    free(data);
}

int main() {
    char* body = "john_doe|Hello, World!";
    Message msg;
    process_message(body, &msg);
    printf("Sender: %s, Message: %s\n", msg.sender, msg.message);
    return 0;
}