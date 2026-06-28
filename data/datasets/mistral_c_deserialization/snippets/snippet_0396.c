#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* sender;
    char* message;
} Message;

void process_message(Message* msg) {
    printf("Sender: %s\n", msg->sender);
    printf("Message: %s\n", msg->message);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <incoming_body>\n", argv[0]);
        return 1;
    }

    char* incoming_body = argv[1];
    Message* msg = (Message*)incoming_body;
    process_message(msg);

    return 0;
}