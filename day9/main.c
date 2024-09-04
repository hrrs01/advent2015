#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

FILE* fptr;

void strstrip(char* str);

typedef struct Road road_t;
typedef struct City city_t;

struct Road {
    int length;
    city_t* targets[2];
};

struct City {
    char name[30];
    road_t* roads[10];
};


city_t* appendCity(city_t* cities, int* cc,  char* name){
    
}


city_t* findCity(city_t* cities, int* cc, char* name){
    for(int i=0; i<20; i++){
        if(strcmp(name, cities[i].name) == 0){
            return &(cities[i]);
        }
    }
    return appendCity(cities, cc, name);
}


int main(){
    road_t* roads = malloc(sizeof(road_t) * 100);
    int road_counter = 0;
    city_t* cities = malloc(sizeof(city_t) * 20);
    int city_counter = 0;
    fptr = fopen("../in.txt", "r");
    char buffer[120] = {0};
    char* token;
    while(fgets(buffer, 120, fptr) != NULL){
        strstrip(buffer);
        token = strtok(buffer, " ");
        int arg_counter = 0;
        char target1[30] = {0};
        char target2[30] = {0};
        int length = 0;
        while(token != NULL){
            if(arg_counter == 0){
                strcpy(target1, token);
            }else if(arg_counter == 2){
                strcpy(target2, token);
            }else if(arg_counter == 4){
                length = atoi(token);
            }
            arg_counter++;
            token = strtok(NULL, " ");
        }
        printf("%s to %s is %u\n", target1, target2, length);
    }
    
    return 0;
    
}
void strstrip(char* str){
    str[strcspn(str, "\n")] = 0;
}
