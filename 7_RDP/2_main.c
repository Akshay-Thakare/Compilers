//
//  main.c
//  5_Recursive_Decent_Parser
//
//  Created by Akshay Thakare on 08/03/15.
//  Copyright (c) 2015 Akshay Thakare. All rights reserved.
//

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char inputSymbol;
char t[10];
int count=0;

void Advance(){
    inputSymbol = t[count];
    count++;
}

void Error(){
    perror("The string doesn't match the grammer.\n");
    exit(EXIT_FAILURE);
}

void B(){
    if(inputSymbol == 'b'){
        Advance();
        B();
    }
    else{
        if(inputSymbol == 'a'){
            Advance();
        }
        else{
            Error();
        }
    }
}

void A(){
    if(inputSymbol == 'a'){
        Advance();
        A();
    }
    else{
        if(inputSymbol == 'b'){
            Advance();
        }
        else{
            Error();
        }
    }
}

void S(){
    A();
    B();
}

int main(){
    printf("Enter the string : ");
    scanf("%s",t);
    Advance();
    S();
    if(count <= strlen(t)){
        Error();
    }
    else{
        printf("The string is valid and is accepted.");
    }
    return 0;
}

/*
 
 OUTPUT
 
 Enter the string : aba
 The string is valid and is accepted
 
 */