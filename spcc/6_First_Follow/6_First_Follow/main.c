//
//  main.c
//  6_First_Follow
//
//  Created by Akshay Thakare on 08/03/15.
//  Copyright (c) 2015 Akshay Thakare. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAXIMUM 10

int main(int argc, const char * argv[]) {
    
    int n;
    printf("Enter the no. of Non-terminals in the grammer = ");
    scanf("%d",&n);
    
    int i;
    char *non_terminal;
    non_terminal = malloc(n*sizeof(char));
    printf("\nEnter the Non-terminals in the grammer = ");
    scanf("%s",non_terminal);
    
    int nt;
    printf("\nEnter the no. of Terminals in the grammer = ");
    scanf("%d",&nt);
    
    char *terminal;
    terminal = malloc(nt*sizeof(char));
    printf("\nEnter the Terminals in the grammer = ");
    scanf("%s",terminal);
    
    char productions[MAXIMUM][MAXIMUM];     //Dynamic allocation not working here
    printf("\nEnter the productions\n");
    for(i=0;i<n;i++){
        printf("\nEnter the production for %c = ",non_terminal[i]);
        scanf("%s",productions[i]);         //The escape character is auto added as we are usign %s not %c
    }
    
    //Core Logic
    
    //Regular exp
    regex_t regex;
    int reti;
    /* Compile regular expression */
    reti = regcomp(&regex, "[a-z]", 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
    
    int j;
    char ch[2];
    char *first_set;
    first_set = malloc(n*sizeof(char));
    //Iterating over all non-terminals
    for(i=0;i<n;i++){
        //Iterating over all productions of that non - terminal
        for(j=0;j<strlen(productions[i]);i++){
            //Storing all first values in array
            first_set[i] = productions[i][j];
        }
    }
    
    int k;
    //Now we resolve all elements whose firsts are non-terminals
    for(i=0;i<n;i++){
        //Since regexec accepts only a string we convert the char to a string
        ch[0]=first_set[i];
        ch[1]='\0';
        //Next we check for non-terminals
        if(regexec(&regex,ch, 0, NULL, 0)){
            //If you reach here it means you have a non-terminal
            //Now we get the position of the non-terminal
            for(k=0;k<n;k++)
                if(non_terminal[k]==first_set[i])
                    break;
            //Now we substiture the first set of that non-terminal in our required referrer
            first_set[i] = first_set[k];
            
            //Assuming that the second character in the production is not a symbol or another non-terminal
            ch[0]=productions[i][1];
            if(!regexec(&regex,ch, 0, NULL, 0))
                printf("\nFirst of %c -> %c %c",non_terminal[i],first_set[i],productions[i][1]);
            
        } else{
            printf("\nFirst of %c -> %c",non_terminal[i],first_set[i]);
        }
    }
    
    return 0;
}

/*
 
 Enter the no. of Non-terminals in the grammer = 3
 
 Enter the Non-terminals in the grammer = ERT
 
 Enter the no. of Terminals in the grammer = 4
 
 Enter the Terminals in the grammer = ase+
 
 Enter the productions
 
 Enter the production for E = a+s
 
 Enter the production for R = e
 
 Enter the production for T = Rs
 
 First of E -> a
 
 First of R -> e
 
 First of T -> e s
 
*/