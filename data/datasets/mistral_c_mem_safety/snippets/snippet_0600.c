#include <stdio.h>
#include <string.h>

void parse_data(char *data, int length) {
    if (data != NULL && length > 0 && length <= 100) {
        for (int i = 0; i < length; i++) {
            printf("Data[%d]: %c\n", i, data[i]);
        }
    } else {
        printf("Invalid data or length\n");
    }
}

int main() {
    char data[] = "Sample data";
    int length = strlen(data);
    parse_data(data, length);
    parse_data(NULL, length);
    parse_data(data, 0);
    parse_data(data, 101);
    return 0;
}