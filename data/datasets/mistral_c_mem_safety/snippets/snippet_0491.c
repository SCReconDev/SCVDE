#include <stdio.h>
#include <string.h>

void process_input(char *input) {
    char buffer[10];
    strcpy(buffer, input);
    printf("Processed input: %s\n", buffer);
}

int main() {
    char user_input[20] = "This is a long string";
    process_input(user_input);
    return 0;
}