#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

FILE* fptr;

void strstrip(char* str);
int escstr(char* str);
int encstr(char* str);

int main(){

    fptr = fopen("input8-1.txt", "r");
    char buffer[50] = {0};
    int basesum = 0;
    int memsum = 0;

    while(fgets(buffer, 50, fptr) != NULL){
        strstrip(buffer);
        //printf("%s\n", buffer);
        int baselen = strlen(buffer);

        int memlen = encstr(buffer);
        //printf("OldLen: %u, NewLen: %u\n", baselen, memlen);
        basesum += baselen;
        memsum += memlen;
    }

    printf("Result: %u", memsum - basesum);

    return 0;
}

int escstr(char *str){
    int default_len = strlen(str);
    int i = 0;
    bool escape = false;
    for(int c=0;c<default_len;c++){
        
        if((char) str[c] == '\\'){
            c++;
            switch ((char) str[c])
            {
                case '\\':
                    break;
                case '\"':
                    break;
                case 'x':
                    c++;
                    c++;
                    break;
                default:
                    i++;
                    break;
            }
        }
        
        
        i++;
    }
    return i-2;
}

int encstr(char *str){
    int default_len = strlen(str);
    int i = 0;
    bool escape = false;
    for(int c=0;c<default_len;c++){
        
        if((char) str[c] == '\\'){
            i++;
        }else if((char) str[c] == '\"'){
            i++;
        }
        i++;
    }
    return i+2;
}

void strstrip(char* str){
    str[strcspn(str, "\n")] = 0;
}