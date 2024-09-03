#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define KEY_SIZE 30
#define MAX_WIRES 1000
#define MAX_COMMANDS 1000

typedef enum {
    NONE,
    NOT,
    AND,
    OR,
    LSHIFT,
    RSHIFT
} gate_t;

FILE *fptr;

bool isNumeric(char*);
void strstrip(char* str);

int main(){

    fptr = fopen("input7-1.txt", "r");
    char buffer[30] = {0};

    while(fgets(buffer, 30, fptr) != NULL){
        // strip end newlines
        strstrip(buffer);

        bool target = false;
        gate_t gate_type = NONE;

        char* token = strtok(buffer, " ");

        while(token != NULL){
            //printf("New Token \n", token);
            if(isNumeric(token)){
            }else{
                if(strcmp(token, "->") == 0){
                    target = true;
                }else if(strcmp(token, "OR") == 0){
                    gate_type = OR;
                }else if(strcmp(token, "AND") == 0){
                    gate_type = AND;
                }else if(strcmp(token, "RSHIFT") == 0){
                    gate_type = RSHIFT;
                }else if(strcmp(token, "NOT") == 0){
                    gate_type = NOT;
                }else if(strcmp(token, "LSHIFT") == 0){
                    gate_type = LSHIFT;
                }else{
                    if(target){
                    }else{
                    }
                }
            }
            token = strtok(NULL, " ");
        }
    }

    return 0;
}



bool isNumeric(char *a){
    return strspn(a, "0123456789") == strlen(a);
}
void strstrip(char* str){
    str[strcspn(str, "\n")] = 0;
}