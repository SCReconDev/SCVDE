#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char sender[50];
    char message[100];
} Message;

void process_message(const char* body) {
    Message* msg = (Message*)malloc(sizeof(Message));
    memcpy(msg, body, sizeof(Message));
    printf("Sender: %s, Message: %s\n", msg->sender, msg->message);
    free(msg);
}

int main() {
    char body[sizeof(Message)];
    memset(body, 0, sizeof(body));
    strcpy(body, "user1");
    strcpy(body + 50, "Hello, world!");

    process_message(body);
    return 0;
}