#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void process_input(char *input) {
    char buffer[10];
    strcpy(buffer, input);
    printf("Processed input: %s\n", buffer);
}

int main() {
    char *input = "This is a very long input string that will cause a buffer overflow";
    process_input(input);
    return 0;
}