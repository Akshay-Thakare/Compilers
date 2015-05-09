//
//  main.c
//  expt_2_macro_processor_pass_1
//
//  Created by Akshay Thakare on 24/01/15.
//  Copyright (c) 2015 Akshay Thakare. All rights reserved.
//

/* The macro processor executes before the assembler so the location counter and memory allocation is not 
    the macro processors job
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char * argv[])
{
    FILE *input, *mnt, *mdt;
    input = fopen("/Users/akshay/Documents/college/spcc/expt_2_macro_processor_pass_1/expt_2_macro_processor_pass_1/INPUT.txt", "r");
    mnt = fopen("/Users/akshay/Documents/college/spcc/expt_2_macro_processor_pass_1/expt_2_macro_processor_pass_1/MNT.txt", "w");
    mdt = fopen("/Users/akshay/Documents/college/spcc/expt_2_macro_processor_pass_1/expt_2_macro_processor_pass_1/MDT.txt", "w");
    if( input == NULL || mnt == NULL || mdt == NULL ){
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    
    /*Storing input source code in memory*/
    char ch[10], all[100][10];
    int i,count=0;
    while(( fscanf(input, "%s",ch) ) != EOF ) {
        if(strcmp(ch, "START")==0)
            break;
        /* Copy the macro's in the array */
        strcpy(all[count++],ch);
    }
    count-=1;   /* To eliminate the program name line in the array */
    
    /* Creating the MDT and MNT */
    int mntc=0, mdt_value=0;
    int flag=0;         //To save current macro in MDT table
    for(i=0;i<count;i++)
    {
        /* Check if the keyword Macro occurs in the program */
        if(strcmp(all[i], "Macro")==0 && flag==0)
        {
            /* If Macro keyword found then store the macro name in the MNT table */
            fprintf(mnt,"%d\t%s\t%d\n",mntc++,all[i+1],mdt_value++);
            flag=1;     /* Indicates that a macro has been found */
            i++;        /* To prevent macro name from being stored in the table */
        }
        else if(flag==1)
        {
            /* Store the recently found macro in MDT table */
            fprintf(mdt,"%d\t%s\n",mdt_value-1,all[i]);
            /* We dont want to store anything beyond MEND for each Macro so we break the loop */
            if(strcmp(all[i], "MEND")==0)
                flag=0;     /* Indicates the coming lines may or maynot be a Macro */
            if(strcmp(all[i], "START")==0){
                //MEND not found
                perror("Error in Program\n");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            /* In case a Macro is not found. Then we have an error in our program */
            perror("Error in Program\n");
            exit(EXIT_FAILURE);
        }
    }
    
    /* Close all files */
    fclose(input);
    fclose(mnt);
    fclose(mdt);
    return 0;
}
