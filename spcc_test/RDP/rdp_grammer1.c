#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 Grammer
 E ® x+T
 T ® (E)
 T ® x
 */

int pos,size;
char input[10];

void E();
void T();

void T(){
    if(input[pos]=='('){
        pos++;
        E();
        if(input[pos]==')'){
            return;
        } else {
            perror("Invalid input");
            exit(1);
        }
    } else if(input[pos]=='x'){
        pos++;
        return;
    } else{
        perror("Invalid input");
        exit(1);
    }
}

void E(){
    if(input[pos]=='x'&&input[pos+1]=='+'){
        pos+=2;
        T();
        return;
    } else {
        perror("Invalid input");
        exit(1);
    }
}

int main(){

    pos = 0;
    
    printf("Enter input string = ");
    scanf("%s",input);
    
    size = sizeof(input);
    
    E();
    
    printf("\nThe string was successfully parsed\n");
    
    return 0;
}