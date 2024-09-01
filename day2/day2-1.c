#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a,b) (((a) < (b)) ? (a) : (b))
FILE *fptr;
int findChar(char str[40], char target, int occ);
void substring(char *buf, char *source, int start, int end);

int main(){
    fptr = fopen("day2-1.txt", "r");
    char lineBuffer[40];
    char target = 'x';
    int sum = 0;
    int ribbon_sum = 0;

    while(fgets(lineBuffer, 40, fptr) != NULL){
        int l, w, h, x1, x2, side1, side2, side3;
        char lstr[10] = {0}, wstr[10] = {0}, hstr[10] = {0};
        int len = strlen(lineBuffer);
        x1 = findChar(lineBuffer, target, 0);
        x2 = findChar(lineBuffer, target, 1);
        substring(lstr, lineBuffer, 0, x1);
        substring(wstr, lineBuffer, x1+1,x2);
        substring(hstr, lineBuffer, x2+1, len);
        l = atoi(lstr); w = atoi(wstr); h = atoi(hstr);

        side1 = l * w; side2 = w * h; side3 = l * h;
        int temp_sum = 2*side1 + 2*side2 + 2*side3 + min(side1, min(side2, side3));
        sum += temp_sum;

        int min_side = min(side1, min(side2, side3));
        int min1, min2;
        if(min_side == side1){
            min1 = l; min2 = w;
        }else if(min_side == side2){
            min1 = w; min2 = h;
        }else{
            min1 = l; min2 = h;
        }

        ribbon_sum += 2 * min1 + 2 * min2;
        ribbon_sum += l * w * h;
        
        printf("l: %d, w: %d, h: %d, sum: %d, totsum: %d\n", l, w, h, temp_sum, sum);
    }
    printf("Ribbon sum: %d", ribbon_sum);
    

    return 0;
}

void substring(char *buf, char *source, int start, int end){
    int i;
    for(i=0; i<end-start; i++){
        buf[i] = source[start+i];
    }
    buf[i+1] = '\0';
}

int findChar(char *str, char target, int occurance){
    int found = 0;
    int len = strlen(str);
    for(int pos=0; pos<len; pos++){
        if(str[pos] == target){
            if(occurance == found){
                return pos;
            }
            found++;
        }
    }
}