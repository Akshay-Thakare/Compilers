//
//  main.c
//  expt_1_Pass_1_Assembler
//
//  Created by Akshay Thakare on 20/01/15.
//  Copyright (c) 2015 Akshay Thakare. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char * argv[]){
    FILE *input, *st, *mot, *out, *frt,*bt;

    /* Opening files */
    input = fopen("/Users/akshay/Documents/college/spcc/expt_1_Pass_1_Assembler/expt_1_Pass_1_Assembler/INPUT.txt","r");
    st = fopen("/Users/akshay/Documents/college/spcc/expt_1_Pass_1_Assembler/expt_1_Pass_1_Assembler/ST.txt","w");
    mot = fopen("/Users/akshay/Documents/college/spcc/expt_1_Pass_1_Assembler/expt_1_Pass_1_Assembler/MOT.txt","r");
    frt = fopen("/Users/akshay/Documents/college/spcc/expt_1_Pass_1_Assembler/expt_1_Pass_1_Assembler/FRT.txt","w");
    bt = fopen("/Users/akshay/Documents/college/spcc/expt_1_Pass_1_Assembler/expt_1_Pass_1_Assembler/BT.txt","w");
    out = fopen("/Users/akshay/Documents/college/spcc/expt_1_Pass_1_Assembler/expt_1_Pass_1_Assembler/OUT.txt","w");

    /*Checking if all files have been successfully opened*/
    if( input == NULL || st == NULL || mot == NULL || out == NULL || frt == NULL || bt == NULL){
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    
    /*Storing input source code in memory*/
    char ch[10], *s, *s2, *s3, all[100][10];
    int i=0,j=0;
    while(( fscanf(input, "%s",ch) ) != EOF ) {
        /* Checking if any imperative instruction is present */
        s = strchr (ch, ',');
        /* If not an imperative instruction */
        if(s==NULL) {
            /* Check if the instruction is an DS instruction */
            s2 = strchr (ch, 39);
            s3 = strrchr(ch,39);
            /* If not a DS instruction */
            if(s2==NULL) {
                /* Directly copy data */
                strcpy(all[i++], ch);
            }
            /* If a DS instruction */
            else {
                /* Split 'x' and store data */
                int length1 = (int)(s2-ch);
                int length2 = (int)(s3-ch);
                //strncpy(all[i++], ch, length1);       //Ignoring Full word symbol for complexity reasons
                strlcpy(all[i++], ch+length1+1, length2-length1);
            }
        }
        /* If the instruciton is an imperative instruction */
        else {
            int length = (int)(s-ch);
            /* Copy register */
            strlcpy(all[i++],ch,length+1);
            //all[i++][0]=ch[0];
            /* Copy Operand */
            strncpy(all[i++], s+length, (int)strlen(ch)-length);
        }
    }
    strcpy(all[i++],"END"); //For proper looping - if removed program wont work trust me i am an engineer :p
    /* To check if soruce code is proper. This is done by the formula => (line*(3)coloumns)%3==0 */
    if((i%3)!=0) {
        perror("Error in program.\n");
        exit(EXIT_FAILURE);
    }
    
    /* Core Logic */
    char label[10], opcode[10], operand[10];
    int flag=0, location_counter=0,line=0;
    
    /* Loop increments by 3 so that we can consider the entire line at once */
    for(j=0;j<i;j+=3) {
        /* To store line number for forward referene table */
        line++;
        
        /* Initializing variables */
        strcpy(label,all[j]);
        strcpy(opcode,all[j+1]);
        strcpy(operand,all[j+2]);
        
        /* In case we encounter an END statement then exit loop */
        if(strcmp(label, "END")==0){
            fprintf(out,"%d \t %s \t %s \t %s\n",location_counter,label,opcode,operand);
            break;
        }
        
        /* To prevent the heavy operation of strcmp from occuring every time and increasing execution time */
        if(flag==0){
            if(strcmp(opcode,"START")==0){
                flag=1;
                fprintf(out,"%d \t %s \t %s \t %s\n",location_counter,label,opcode,operand);
            }
        }
        else
        {
            if(strcmp(label, "USING")==0)
            {
                /* To populate Base Table */
                int m;
                for(m=0;m<atoi(operand);m++)
                {
                    fprintf(bt, "%s\t%d\t%d\n","N",0,m);
                }
                
                if(strcmp(opcode, "*")==0)
                {
                    /* Storing refernce in BASE table */
                    fprintf(bt, "%s\t%d\t%d\n","Y",0,atoi(operand));
                    //BT    *   15  <- input
                    //BT    0   15  <- output
                }
                else
                {
                    /* Storing refernce in BASE table */
                    fprintf(bt, "%s\t%d\t%d\n","Y",atoi(opcode),atoi(operand));
                }
                
                /* To populate base table */
                for(m=atoi(operand)+1;m<=15;m++)
                {
                    fprintf(bt, "%s\t%d\t%d\n","N",0,m);
                }
                
                /* To print output */
                fprintf(out,"%d \t %s \t %s \t %s\n",location_counter,label,opcode,operand);
            }
            else if(strcmp(opcode, "DC")==0)
            {
                //Considering only full words - coz we have one hell of practical exams which test our typing speed and rot memory
                
                /* Storing reference in Symbol Table */
                fprintf(st,"%s\t%d\t%d\n",label,location_counter,atoi(operand));
                
                fprintf(out,"%d \t %s \t %s \t %s\n",location_counter,label,opcode,operand);
                location_counter+=4;
            }
            else if(strcmp(opcode, "DS")==0)
            {
                //Replace operand by underscore
                fprintf(st,"%s\t%d\t%d\n",label,location_counter,atoi(operand));
                
                //Replace operand by underscore - to maintain consistency with lecture notes
                strcpy(operand, "_");
                
                fprintf(out,"%d \t %s \t %s \t %s\n",location_counter,label,opcode,operand);
                location_counter+=4;
            }
            //if(strcmp(label, "L")==0||strcmp(label, "A")==0||strcmp(label, "ST")==0)
            else
            {
                //Check label with MOT opcode
                char replacement[10];
                int flagged=1;
                while(( fscanf(mot, "%s%s",ch,replacement) ) != EOF ) {
                    if(strcmp(label, ch)==0) {
                        flagged = strcmp(label, replacement);
                    }
                }
                
                /* Checking if symbol exists in MOT */
                if(flagged==1)
                {
                    perror("Error in program. Somethings missing!!!\n");
                    exit(EXIT_FAILURE);
                }
                
                /*
                 
                 Use this code to use FRT table - as of now this is depricated until further notice
                 
                //Store symbol in forward reference table
                //Structure => LINE_NO  SYMBOL
                //fprintf(frt,"%d\t%s\n",line,operand);
                
                //Replace operand by underscore - to maintain consistency with lecture notes
                //strcpy(operand, "_");
                */
                 
                fprintf(out,"%d \t %s \t %s \t %s\n",location_counter,label,opcode,operand);
                location_counter+=4;
                
                rewind(mot);        //V.IMP step
            }

        }
        
    }
    
    
    if(flag==0) {       //That is START was not found in the program
        perror("Error in program.\n");
        exit(EXIT_FAILURE);
    }
    /* Close all files */
    fclose(input);
    fclose(st);
    fclose(mot);
    fclose(frt);
    fclose(bt);
    fclose(out);
    return 0;
}

