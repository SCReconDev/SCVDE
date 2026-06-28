#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* sender;
    char* message;
} Message;

void load_message(const char* data, Message* msg) {
    char* token = strtok((char*)data, ";");
    msg->sender = strdup(token);
    token = strtok(NULL, ";");
    msg->message = strdup(token);
}

int main() {
    char message_data[] = "user1;Hello, world!";
    Message msg;
    load_message(message_data, &msg);

    printf("Sender: %s, Message: %s\n", msg.sender, msg.message);
    free(msg.sender);
    free(msg.message);

    return 0;
}