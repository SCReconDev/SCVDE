#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void process_input(char *input) {
    char buffer[10];
    strcpy(buffer, input);
    printf("Processed input: %s\n", buffer);
}

int main() {
    char *user_input = "This is a very long input that will cause a buffer overflow";
    process_input(user_input);
    return 0;
}