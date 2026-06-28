#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char sender[50];
    char message[100];
} Message;

void deserialize_message(Message *msg, const char *data) {
    char *token = strtok((char *)data, ";");
    strcpy(msg->sender, token);
    token = strtok(NULL, ";");
    strcpy(msg->message, token);
}

void process_message(const char *body) {
    Message msg;
    deserialize_message(&msg, body);
    printf("Message processed: Sender=%s, Message=%s\n", msg.sender, msg.message);
}

int main() {
    const char *body = "user;Hello, world!";
    process_message(body);
    return 0;
}