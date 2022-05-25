#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (void) {
    char *prefix = "prefix";
    char *buffer = "line01";
    char *result = malloc(1000);
    
    strcpy(result, prefix);
    strcat(result, buffer);
    
    printf("%s", result);
    return 0;
}
