//
//  main.c
//  FirstSet
//
//  Created by Akshay Thakare on 18/04/15.
//  Copyright (c) 2015 Akshay Thakare. All rights reserved.
//

/*
 
 Rules for first set
 1. If X is a terminal then First(X) is just X
 2. If there is a Production X -> ε then just add ε to first(X)
 3. If there is a Production X -> Y1 | Y2 | Y3 | ... | Yk then add first(Y1 Y2 Y3 .. Yk) to first(X)
 4. If First(Y1 Y2 .. Yk) is either
    a. First(Y1)(if First(Y1) does not contain ε)
    b. OR (if First(Y1 contains ε) then) First(Y1 Y2 .. Yk) is everything in First(Y1)<except ε> as well as 
        everything in First(Y2 Y3 .. Yk)
    c. if First(Y1) First(Y2)...First(Yk) all contains ε then add ε to First(Y1 Y2 ... Yk) as well
 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, const char * argv[]) {
    
    FILE *input;
    input = fopen("/Users/akshay/Documents/college/spcc/FirstSet/FirstSet/input", "r");
    
    char global_non_term[10][5];
    
    int count=0,added_to_non_term=0;
    char ch[10],non_term[10], productions[10],first_set[10][10];
    while((fscanf(input, "%s",ch) ) != EOF ) {
        
        //Scan input till '->' is encountered
        int i,j,k;
        for(i=0;ch[i]!='-';i++)
            non_term[i] = ch[i];
        
        //Scanning productions after '->'
        k=0;
        for(j=i+2;ch[j]!='\0';j++)
            productions[k++] = ch[j];
        
        /*
         E->TE'
         E'->+TE
         E'->ε
         T->FT'
         T'->*FT'
         T'->ε
         F->(E)
         F->id
         */
        
        int mark_duplicate_point=0;
        //Removing duplicate non-terminals
        int temp=0;
//        printf("s- %d\n",strcmp(global_non_term[i], non_term));
        for(i=0;i<added_to_non_term;i++){
            if(strcmp(global_non_term[i], non_term)==0){
                temp++;
                mark_duplicate_point = i;
            }
        }
        
        //Similar element does not exist
        if(temp==0){
            strcpy(global_non_term[added_to_non_term], non_term);
            added_to_non_term++;
        }
        
        //Calculating first sets
        
        //If non terminal then
        if(isupper(productions[0])){
            printf("s - %s\n",non_term);
        } else{
            char c_temp[2];
            c_temp[0] = productions[0];
            c_temp[1] = ',';
            strcat(first_set[mark_duplicate_point], c_temp);
        }
        
        //Needed to re initialize array
        count++;
        memset(non_term,0,10);
        memset(productions,0,10);
    }
    
    int i;
    for(i=0;i<added_to_non_term;i++)
        printf("%s - { %s }\n",global_non_term[i],first_set[i]);
    
    return 0;
}
