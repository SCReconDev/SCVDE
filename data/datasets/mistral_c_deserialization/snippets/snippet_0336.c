#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char sender[50];
    char message[100];
} Message;

void process_message(const char* body, Message* msg) {
    sscanf(body, "%49s %99[^\n]", msg->sender, msg->message);
}

void handle_message(const char* body) {
    Message msg;
    process_message(body, &msg);
    printf("Message from %s: %s\n", msg.sender, msg.message);
}

int main() {
    char body[200];
    printf("Enter message body: ");
    fgets(body, sizeof(body), stdin);
    handle_message(body);
    return 0;
}