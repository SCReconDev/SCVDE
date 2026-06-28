#include <stdio.h>
#include <stdlib.h>

void process_input(char *input) {
    char buffer[10];
    strncpy(buffer, input, strlen(input));
    printf("Processed input: %s\n", buffer);
}

int main() {
    char *input = "This is a very long input string that will cause a buffer overflow";
    process_input(input);
    return 0;
}