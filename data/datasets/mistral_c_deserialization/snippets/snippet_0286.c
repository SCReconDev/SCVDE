#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char sender[50];
    char message[100];
} Message;

void process_message(Message *msg, const char *data) {
    sscanf(data, "%49s %99[^\n]", msg->sender, msg->message);
}

void handle_message(const char *data) {
    Message msg;
    process_message(&msg, data);
    printf("Message from %s: %s\n", msg.sender, msg.message);
}

int main() {
    char data[200];
    printf("Enter message data: ");
    fgets(data, sizeof(data), stdin);
    handle_message(data);
    return 0;
}