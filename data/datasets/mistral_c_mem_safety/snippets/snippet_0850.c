#include <stdio.h>
#include <string.h>

void parse_data() {
    char data[] = "12345";
    int length = strlen(data);

    if (length < 1 || length > 5) {
        printf("Invalid data length\n");
        return;
    }

    printf("Parsed data: %s\n", data);
}

int main() {
    parse_data();
    return 0;
}