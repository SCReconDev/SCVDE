#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x;
    int y;
} Point;

void restore_point(Point* point, const char* data) {
    char* token = strtok((char*)data, ",");
    point->x = atoi(token);
    token = strtok(NULL, ",");
    point->y = atoi(token);
}

int main() {
    char* data = "10,20";
    Point point;
    restore_point(&point, data);
    printf("Point: (%d, %d)\n", point.x, point.y);
    return 0;
}