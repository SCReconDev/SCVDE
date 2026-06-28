#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int value;
} Preference;

void import_preferences(char* file) {
    Preference* pref = (Preference*)malloc(sizeof(Preference));
    memcpy(pref, file, sizeof(Preference));
    printf("Preference: %s\n", pref->name);
    free(pref);
}

int main() {
    char file[1024];
    fgets(file, sizeof(file), stdin);
    import_preferences(file);
    return 0;
}