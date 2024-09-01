#include "stdio.h"
#include "stdbool.h"
FILE *fptr;

int main(){
    int floor = 0;
    int rides = 0;
    bool basement_found = false;
    fptr = fopen("input1-1.txt", "r");
    char commands[9000] = {0};
    fgets(commands, 9000, fptr);
    for(int i=0; i<9000; i++){
        rides += 1;
        switch (commands[i])
        {
        case '(':
            floor++;
            break;
        case ')':
            floor--;
            if(!basement_found && floor < 0){
                printf("Rides to basement: %d\n", rides);
                basement_found = true;
            }
            break;
        
        default:
            break;
        }
    }

    printf("Final floor: %d", floor);

    return 0;


}