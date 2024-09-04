#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

FILE* fptr;

int main(){

    fptr = fopen("in.txt", "r");
    char buffer[40] = {0};
    printf("Hello, World!");
    printf("Hello, World2!");
    
    
    return 0;
    
}
