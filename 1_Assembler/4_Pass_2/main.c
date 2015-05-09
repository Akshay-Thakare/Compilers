//
//  main.c
//  expt_1_Pass_2_Assembler
//
//  Created by Akshay Thakare on 21/01/15.
//  Copyright (c) 2015 Akshay Thakare. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char * argv[]){
    FILE *input, *st, *mot, *out, *frt,*bt;
    input = fopen("/Users/akshay/Documents/college/spcc/expt_1_Pass_1_Assembler/expt_1_Pass_1_Assembler/OUT.txt","r");
    st = fopen("/Users/akshay/Documents/college/spcc/expt_1_Pass_1_Assembler/expt_1_Pass_1_Assembler/ST.txt","r");
    mot = fopen("/Users/akshay/Documents/college/spcc/expt_1_Pass_1_Assembler/expt_1_Pass_1_Assembler/MOT.txt","r");
    frt = fopen("/Users/akshay/Documents/college/spcc/expt_1_Pass_1_Assembler/expt_1_Pass_1_Assembler/FRT.txt","r");
    bt = fopen("/Users/akshay/Documents/college/spcc/expt_1_Pass_1_Assembler/expt_1_Pass_1_Assembler/BT.txt","r");
    out = fopen("/Users/akshay/Documents/college/spcc/expt_1_Pass_1_Assembler/expt_1_Pass_1_Assembler/OUT2.txt","w");
    if( input == NULL || st == NULL || mot == NULL || out == NULL || frt == NULL || bt == NULL){
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    
    //Read input from pass 1
    char ch[10], input_code[100][10];
    int i=0,j=0;
    while(( fscanf(input, "%s",ch) ) != EOF ) {
        strcpy(input_code[i++], ch);
    }
    
    //Read Base Table
    int base_register=0;
    int base_register_value=0;
    int m;
    char avail;
    for(m=0;m<=15;m++)
    {
        fscanf(bt, "%s\t%d\t%d",&avail,&base_register_value,&base_register);
        if(avail=='Y')
            break;
    }
    
    //Logic Processing
    char label[10], opcode[10], operand[10];
    int flag=0, memory_location=0,line=0;
    
    for(j=0;j<i;j+=4)
    {
        line++;     //To keep track of program line number
        memory_location = atoi(input_code[j]);
        strcpy(label,input_code[j+1]);
        strcpy(opcode,input_code[j+2]);
        strcpy(operand,input_code[j+3]);

        if(strcmp(label, "END")==0){
            fprintf(out,"%d",memory_location);
            break;
        }
        
        if(flag==0){     //To prevent the heavy operation of strcmp from occuring every time and increasing execution time
            if(strcmp(opcode,"START")==0){
                flag=1;
                fprintf(out,"%d\n",memory_location);
            }
        }
        else
        {
            if(strcmp(opcode,"USING")==0){
                fprintf(out,"%d\n",memory_location);
            }
            else if(strcmp(opcode, "DC")==0 || strcmp(opcode, "DS")==0) {
                fprintf(out,"%d \t %s\n",memory_location, operand);
            }
            else
            {
                /* Checking forward reference table for current line - depricated */
                int cur_line=0;
                /*
                 
                 //Use this code only if you want to use FRT table
                 
                 while(( fscanf(frt,"%d\t%s\n",&cur_line,ch) ) != EOF ) {
                    if(cur_line==line)
                        break;
                }
                 */
                
                char ch2[10];
                int operand_value=0;
                int temp=0;
                /* Retrieving current line label value from Symbol Table */
                while(( fscanf(st,"%s\t%d\t%d\n",ch2,&cur_line,&temp) ) != EOF ) {
                    if(strcmp(ch2, operand)==0)
                        operand_value = cur_line;
                }
                
                //Replace label with MOT opcode
                char replacement[10];
                while(( fscanf(mot, "%s%s",ch,replacement) ) != EOF ) {
                    if(strcmp(label, ch)==0) {
                        strcpy(label, replacement);
                    }
                }
                
                fprintf(out,"%d \t %s \t %s,%d(%d,%d)\n",memory_location,label,opcode,operand_value,base_register_value,base_register);
                
                /* Re - initializing file pointers */
                rewind(frt);
                rewind(st);
                rewind(mot);
            }
        }
    }
    
    /* Closing all files */
    fclose(input);
    fclose(st);
    fclose(mot);
    fclose(frt);
    fclose(bt);
    fclose(out);
    return 0;
}