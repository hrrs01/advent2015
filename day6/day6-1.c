#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 1000
#define COLS 1000

FILE *fptr;

int idx(int x, int y){
    return y * COLS + x;
}

int on(int *lights, int startX, int endX, int startY, int endY);
int off(int *lights, int startX, int endX, int startY, int endY);
int toggle(int *lights, int startX, int endX, int startY, int endY);

typedef enum {
    ON,
    OFF,
    TOGGLE
} command;

int main(){
    const char *delim = " ";
    const char *delim2 = ",";
    int *lights = malloc(sizeof(*lights) * ROWS * COLS);
    fptr = fopen("input6-1.txt", "r");
    char buffer[40];
    char *token;
    int brightness = 0;

    while(fgets(buffer, 40, fptr) != NULL){
        printf("%s", buffer);
        command current_command;
        bool firstNum = true;
        bool secondNum = false;
        char num1[10] = {0};
        char num2[10] = {0};
        int startX, startY, endX, endY;
        token = strtok(buffer, delim);
        while(token != NULL){
            if(strcmp("turn", token) == 0){
            }else if(strcmp("toggle", token) == 0){
                current_command = TOGGLE;
            }else if(strcmp("on", token) == 0){
                current_command = ON;
            }else if(strcmp("off", token) == 0){
                current_command = OFF;
            }else if(strcmp("through", token) == 0){
                firstNum = false;
                secondNum = true;
            }else{
                if(firstNum){
                    strcpy(num1, token);
                }else if(secondNum){
                    strcpy(num2, token);
                    secondNum = false;
                }
            }
            token = strtok(NULL, delim);
        }
        char *num_token = strtok(num1, delim2);
        startX = atoi(num_token);
        num_token = strtok(NULL, delim2);
        startY = atoi(num_token);
        num_token = strtok(num2, delim2);
        endX = atoi(num_token);
        num_token = strtok(NULL, delim2);
        endY = atoi(num_token);

        switch(current_command){
            case TOGGLE:
                toggle(lights, startX, endX, startY, endY);
                break;
            case ON:
                on(lights, startX, endX, startY, endY);
                break;
            case OFF:
                off(lights, startX, endX, startY, endY);
                break;
        }
        printf("current_command: %d, startX: %d, startY: %d, endX: %d, endY: %d\n", current_command, startX, startY, endX, endY);
    }
    for(int x=0;x<ROWS;x++){
        for(int y=0;y<COLS;y++){
            brightness += lights[idx(x,y)];
        }
    }
    printf("Total brightness: %d", brightness);
    return 0;
}

int on(int *lights, int startX, int endX, int startY, int endY){
    for(int x=startX;x<=endX;x++){
        for(int y=startY;y<=endY;y++){

            lights[idx(x,y)] += 1;
            
        }
    }
    return 0;
}

int off(int *lights, int startX, int endX, int startY, int endY){
    for(int x=startX;x<=endX;x++){
        for(int y=startY;y<=endY;y++){
            lights[idx(x,y)] -= lights[idx(x,y)]?(1):(0);
        }
    }
    return 0;
}

int toggle(int *lights, int startX, int endX, int startY, int endY){
    for(int x=startX;x<=endX;x++){
        for(int y=startY;y<=endY;y++){
            lights[idx(x,y)] += 2;
        }
    }
    return 0;
}




