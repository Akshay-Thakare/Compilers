#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
 Grammer
 S ® aSb
 S ® ab
 
 Factoring brings us:
 S ® aZ
 Z ® Sb
 Z ® b
 
 which is not quite the form we want since it is unclear when to apply the Z-productions. Substituting for S will solve this problem and produce the following productions that are exactly what we want to have.
 
 S ® aZ
 Z ® aZb
 Z ® b
 
 */

int pos,size;
char input[10];

void S();
void Z();

void Z(){
    if(input[pos]=='a'){
        pos++;
        Z();
        if(input[pos]=='b'){
            pos++;
            return;
        } else{
            perror("Invalid Input");
            exit(1);
        }
    } else if (input[pos]=='b'){
        pos++;
        return;
    } else {
        perror("Invalid Input");
        exit(1);
    }
}

void S(){
    if(input[pos]=='a'){
        pos++;
        Z();
        return;
    } else {
        perror("Invalid Input");
        exit(1);
    }
}

int main(){

    pos = 0;
    
    printf("Enter input string = ");
    scanf("%s",input);
    
    size = sizeof(input);
    
    S();
    
    printf("\nThe string was successfully parsed\n");
    
    return 0;
}