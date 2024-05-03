#include <stdio.h>
#include <string.h>
#define BUFFSIZE 1024

int main(int argc, char *argv[]) {
    char name[BUFFSIZE];
    strcpy(name, argv[1]);
    strcat(name, " ");
    strcat(name, argv[2]);
    printf("name: %s\n", name);
    return 0;
}
