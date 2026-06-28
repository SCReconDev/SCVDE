#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char sender[50];
    char message[100];
} Message;

void load_message(const char* data, Message* msg) {
    char* decoded_data = malloc(strlen(data) + 1);
    strcpy(decoded_data, data);
    sscanf(decoded_data, "%49s %99[^\n]", msg->sender, msg->message);
    free(decoded_data);
}

void process_message(const char* message_data) {
    Message msg;
    load_message(message_data, &msg);
    printf("Message from %s: %s\n", msg.sender, msg.message);
}

int main() {
    const char* message_data = "john Hello, how are you?";
    process_message(message_data);
    return 0;
}