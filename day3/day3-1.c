#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define ROWS 3000
#define COLS 3000

FILE *fptr;
int main(){
    fptr = fopen("input3-1.txt", "r");
    fseek(fptr, 0L, SEEK_END);
    int filesize = ftell(fptr);
    fseek(fptr, 0L, SEEK_SET);
    char *buffer = malloc(filesize);
    bool (*house)[COLS];
    bool robo = true;
    house = malloc(sizeof(bool[ROWS][COLS]));

    int pos=0,santa_x=ROWS/2,santa_y=COLS/2,robo_x=santa_x, robo_y=santa_y;

    fgets(buffer, filesize, fptr);
    int sum = 1;
    house[robo_x][robo_y] = true;
    for(;pos<filesize;pos++){
        switch (buffer[pos])
        {
        case '<':
            robo?(robo_x--):(santa_x--);
            break;
        case '^':
            robo?(robo_y++):(santa_y++);
            break;
        case '>':
            robo?(robo_x++):(santa_x++);
            break;
        case 'v':
            robo?(robo_y--):(santa_y--);
            break;
        }
        if(!house[robo?(robo_x):(santa_x)][robo?(robo_y):(santa_y)]){
            house[robo?(robo_x):(santa_x)][robo?(robo_y):(santa_y)] = true;
            sum += 1;
        }
        robo = !robo;

    }
    printf("Number of gifts given: %d", sum);
        
    return 0;
}