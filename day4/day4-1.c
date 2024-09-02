#include <stdio.h>
#include <md5.h>
#include <stdbool.h>
#include <string.h>

int main(){
    uint8_t results[16] = {0};
    char key[] = "iwrupvqb";

    for(int i=0;i<100000000;i++){
        char tempKey[50] = {0};
        char tempNum[20] = {0};
        strcat(tempKey, key);
        sprintf(tempNum, "%d", i);
        strcat(tempKey, tempNum);

        md5String(tempKey, results);
        char tempTest[11] = {0};
        for(int x=0; x<3; x++){
            char tempRes[3] = {0};
            sprintf(tempRes, "%x", results[x]);
            strcat(tempTest, tempRes);
        }
        if(strlen(tempTest) < 4 && tempTest[0] == '0' & tempTest[1] == '0' & tempTest[2] == '0'){
            printf("Answer: %d, results: %s\n", i, tempTest);
            break;
        }
        

    }
    
    for(int i=0; i<16; i++){
        printf("%x", results[i]);
    }
    printf("\n");
    
    return 0;
}