#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_WIRES 200

typedef struct {
    char key[30];
    uint16_t count;
} wire;

void wirelist_append(wire *wirelist, int *counter, wire newwire){
    printf("Appending! \n");
    wirelist[*counter] = newwire;
    *counter += 1;
    printf("Counter is currently: %d\n", *counter);
}

wire* wirelist_get(wire *wirelist, int *counter, char *keyword){
    
    for(int i=0;i<(*counter);i++){
        if(strcmp(wirelist[i].key, keyword) == 0){
            return &wirelist[i];
        }
    }
    wire newwire;
    strcpy(newwire.key, keyword);
    newwire.count = 0;
    wirelist_append(wirelist, counter, newwire);
    return &wirelist[*counter];
}

typedef enum {
    NONE,
    AND,
    OR,
    NOT,
    RSHIFT,
    LSHIFT    
} gate_type;


FILE *fptr;

bool isNumeric(char*);
void apply(wire *wirelist, int* wireCounter, char target[], char args[2][5], int argCount, uint16_t num, gate_type gate);

int main(){

    wire *wirelist = malloc(sizeof(wire) * MAX_WIRES);
    int *wireCounter = malloc(sizeof(int) * 3);
    *wireCounter = 0;
    fptr = fopen("input7-1.txt", "r");
    char buffer[30] = {0};

    while(fgets(buffer, 30, fptr)){
        buffer[strcspn(buffer, "\n")] = 0; // Strip newline

        char* token = strtok(buffer, " ");
        uint16_t num = 0;
        char args[2][5] = {0};
        int argCount = 0;
        gate_type gate = NONE;
        while(token != NULL){
            if(isNumeric(token)){
                num = atoi(token);
            }else{
                if(strcmp(token, "->") == 0){
                    token = strtok(NULL, " ");
                    apply(wirelist, wireCounter, token, args, argCount, num, gate);
                }else if(strcmp(token, "OR") == 0){
                    gate = OR;
                }else if(strcmp(token, "AND") == 0){
                    gate = AND;
                }else if(strcmp(token, "RSHIFT") == 0){
                    gate = RSHIFT;
                }else if(strcmp(token, "NOT") == 0){
                    gate = NOT;
                }else if(strcmp(token, "LSHIFT") == 0){
                    gate = LSHIFT;
                }else{
                    strcpy(args[argCount], token);
                    argCount++;
                }
            }

            token = strtok(NULL, " ");
        }
    }
    return 0;
}

void apply(wire *wirelist, int* wireCounter, char target_key[], char args[2][5], int argCount, uint16_t num, gate_type gate){
    wire* target = wirelist_get(wirelist, wireCounter, target_key);
    switch(argCount){
        case 0:  
            target->count = num;
            printf("Wire %s set to %u \n", target->key, target->count);
            return;
            break;
        case 1:
            wire* arg = wirelist_get(wirelist, wireCounter, args[0]);
            switch(gate){
                case AND:
                    target->count = arg->count & num;
                    printf("Wire %s set to %u & %s = %u \n", target->key, num, arg->key, target->count);
                    break;
                case OR:
                    target->count = arg->count | num;
                    printf("Wire %s set to %u | %s = %u \n", target->key, num, arg->key, target->count);
                    break;
                case NOT:
                    target->count = ~(arg->count);
                    printf("Wire %s set to ~%s = %u \n", target->key, arg->key, target->count);
                    break;
                case LSHIFT:
                    target->count = arg->count << num;
                    printf("Wire %s set to %s << %u = %u \n", target->key, arg->key, num, target->count);
                    break;
                case RSHIFT:
                    target->count = arg->count >> num;
                    printf("Wire %s set to %s >> %u = %u \n", target->key, arg->key, num, target->count);
                    break;
            }
            break;
        case 2:
            wire* arg1 = wirelist_get(wirelist, wireCounter, args[0]);
            wire* arg2 = wirelist_get(wirelist, wireCounter, args[1]);
            printf("WireCounter: %d\n ", *wireCounter);
            switch(gate){
                case AND:
                    (*target).count = arg1->count & arg2->count;
                    printf("Wire %s set to %s & %s = %u \n", target->key, arg1->key, arg2->key, target->count);
                    break;
                case OR:
                    //(*target).count = arg->count | arg2->count;
                    printf("Wire %s set to %s | %s = %u \n", target->key, arg1->key, arg2->key, target->count);
                    break;
            }
            break;
    }
}

bool isNumeric(char *a){
    return strspn(a, "0123456789") == strlen(a);
}