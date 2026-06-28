#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char sender[50];
    char message[200];
} Message;

void deserialize_message(char* data, Message* msg) {
    char* token = strtok(data, ";");
    strcpy(msg->sender, token);
    token = strtok(NULL, ";");
    strcpy(msg->message, token);
}

void process_message(char* body) {
    Message msg;
    deserialize_message(body, &msg);
    printf("Processed message from %s: %s\n", msg.sender, msg.message);
}

int main() {
    char body[] = "Alice;Hello, Bob!";
    process_message(body);
    return 0;
}