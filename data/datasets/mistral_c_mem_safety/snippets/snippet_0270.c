#include <stdio.h>
#include <string.h>

void parse_data(char *data, int length) {
    if (length > 0 && length < 100) {
        char buffer[length];
        strcpy(buffer, data);
        printf("Parsed data: %s\n", buffer);
    }
}

int main() {
    char *data = "This is a very long string that will cause a buffer overflow";
    parse_data(data, 200);
    return 0;
}