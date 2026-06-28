#include <stdio.h>
#include <string.h>

void handle_input(char* input, size_t input_size) {
    char buffer[100];
    if (input_size < sizeof(buffer)) {
        memcpy(buffer, input, input_size);
        buffer[input_size] = '\0';
        printf("Input: %s\n", buffer);
    } else {
        printf("Input too large\n");
    }
}

int main() {
    char input[] = "Hello, World!";
    handle_input(input, strlen(input));
    return 0;
}