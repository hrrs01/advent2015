#include <stdio.h>
#include <stdbool.h>
#include <string.h>

FILE *fptr;

bool checkVowels(char arr1[], char arr2[]);
bool checkDouble(char str[]);
bool checkNaughty(char str[]);
bool checkPair(char str[]);
bool checkWall(char str[]);

int main(){

    fptr = fopen("input5-1.txt", "r");
    int count = 0;
    char buffer[25] = {0};
    char vowels[] = "aeoiu";
    while(fgets(buffer, 25, fptr) != NULL){
        //bool nice = checkVowels(vowels, buffer) && checkDouble(buffer) && !checkNaughty(buffer);
        bool nice = checkPair(buffer) && checkWall(buffer);

        if(nice){
            printf("%s", buffer);
            count++;
        }
    }
    printf("Number of nice: %d", count);

    return 0;
}

bool checkVowels(char vowels[], char str[]){
    int count = 0;
    int len_vowels = strlen(vowels);
    int len_str = strlen(str);
    for(int i=0;i<len_str;i++){
        for(int y=0;y<len_vowels;y++){
            if(vowels[y] == str[i]){
                printf("Vowels: %s\n", vowels);
                printf("%c == %c\n", vowels[y], str[i]);
                count += 1;
                break;
            }
        }
        if(count>2){
            printf("Vowel Count: %d\n", count);
            return true;
        }
    }
    return false;

}

bool checkDouble(char str[]){
    int len_str = strlen(str);
    bool first = true;
    char last_char = ' ';
    for(int i=0;i<len_str;i++){
        if(!first && last_char == str[i]){
            printf("Double char: %c\n", str[i]);
            return true;
        }
        first = false;
        last_char = str[i];
    }
    return false;
}

bool checkNaughty(char str[]){
    int len_str = strlen(str);
    char last_char = ' ';
    for(int i=0;i<len_str;i++){
        if((last_char == 'a' && str[i] == 'b') || (last_char == 'c' && str[i] == 'd') 
            || (last_char == 'p' && str[i] == 'q') || (last_char == 'x' && str[i] == 'y')){
            return true;
        }
        last_char = str[i];
    }
    printf("Not Naughty\n");
    return false;
}

bool checkPair(char str[]){
    int len_str = strlen(str);
    char last_char = str[0];
    for(int i=1;i<len_str-1;i++){
        char last_temp_char = str[i+1];
        for(int y=i+2;y<len_str;y++){
            if(str[i] == str[y] && last_temp_char == last_char){
                printf("%c%c == %c%c\n", last_char, str[i], last_temp_char, str[y]);
                return true;
            }
            last_temp_char = str[y];
        }
        last_char = str[i];
    }
    return false;
}

bool checkWall(char str[]){
    int len_str = strlen(str);
    char lastlast_char = ' ';
    char last_char = ' ';
    for(int i=0;i<len_str;i++){

        if(lastlast_char == str[i]){
            return true;
        }

        lastlast_char = last_char;
        last_char = str[i];
    }
    return false;
}