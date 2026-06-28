#include <stdio.h>
#include <string.h>

void parse_data(char *data, int length) {
    if (length > 0 && length < 100) {
        printf("Parsed data: %s\n", data);
    }
}

int main() {
    char input[150] = "This is a long input string";
    parse_data(input, 150);
    return 0;
}