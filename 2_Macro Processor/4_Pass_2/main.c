//
//  main.c
//  expt_2_macro_processor_pass_2
//
//  Created by Akshay Thakare on 24/01/15.
//  Copyright (c) 2015 Akshay Thakare. All rights reserved.
//

/* Expand source code */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char * argv[])
{
    FILE *input, *out, *mnt, *mdt;
    input = fopen("/Users/akshay/Documents/college/spcc/expt_2_macro_processor_pass_1/expt_2_macro_processor_pass_1/INPUT.txt", "r");
    out = fopen("/Users/akshay/Documents/college/spcc/expt_2_macro_processor_pass_1/expt_2_macro_processor_pass_1/OUT.txt", "w");
    mnt = fopen("/Users/akshay/Documents/college/spcc/expt_2_macro_processor_pass_1/expt_2_macro_processor_pass_1/MNT.txt", "r");
    mdt = fopen("/Users/akshay/Documents/college/spcc/expt_2_macro_processor_pass_1/expt_2_macro_processor_pass_1/MDT.txt", "r");
    if( input == NULL || mnt == NULL || mdt == NULL || out == NULL ){
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    
    /* Read input file */
    char ch[10], input_file[100][10],out_file[100][10],*s;
    int i=0;
    
    /* Skippin code till START is encountered */
    while(( fscanf(input, "%s",ch) ) != EOF ) {
         strcpy(input_file[i++], ch);
        if(strcmp(input_file[i-1], "START")==0)
            break;
    }
    
    /* Copying Program name and START to out_file array */
    strcpy(out_file[0],input_file[i-2]);
    strcpy(out_file[1],input_file[i-1]);
    i=2;
    while(( fscanf(input,"%s",ch) ) != EOF ) {
        s = strchr (ch, ',');
        if(s==NULL) {
            strcpy(out_file[i++], ch);
        }
        else {
            /* Splitting on comma */
            int length = (int)(s-ch);
            /* Copy register */
            strlcpy(out_file[i++],ch,length+2);
            /* Copy Operand */
            strncpy(out_file[i++], s+length, (int)strlen(ch)-length);
        }
    }
    
    /* End of reaading file */
    
    /* Read MNT table */
    int mntc[100],mdt_value[100], mnt_count=0;
    char mnt_symbol[100][10];
    while(( fscanf(mnt, "%d\t%s\t%d",&mntc[mnt_count],mnt_symbol[mnt_count],&mdt_value[mnt_count]) ) != EOF ){
        mnt_count++;
    }
    
    char output_array[100][10];
    /* Expaning source code */
    int j,k,flag=0,index=0,m=0,n=0;
    for(j=0;j<i;j++) {
        /* Searching each input for Macro name */
        for(k=0;k<mnt_count;k++) {
            if(strcmp(out_file[j], mnt_symbol[k])==0) {     /* Scans through all Macros from MNT table */
                flag=1;                 /* Denotes that a macro has been found and needs to be expanded */
                index=mdt_value[k];     /* Storing MDT Value for reference */
            }
        }
        rewind(mnt);                /* In case same macro occurs twice */
        if(flag==1) /* Macro found */
        {
            int temp;
            /* Load macro from MDT into the output array */
            while(( fscanf(mdt,"%d\t%s\n",&temp, ch) ) != EOF ) {       /* Reads from MDT table */
                if(temp==index){    /* Only those values which are of the current Macro are checked */
                    if(strcmp(ch, "MEND")==0)
                        break;      /*We dont want MEND in our output so we break the loop */
                    
                    /*To seperate comma's from MDT description*/
                    s = strchr (ch, ',');
                    if(s==NULL) {
                        /* In case we dont have a comma */
                        strcpy(output_array[m++],ch);
                    }
                    else {
                        int length = (int)(s-ch);
                        /* Copy register */
                        strlcpy(output_array[m++],ch,length+2); /* Length+2 bcoz we need the ',' too */
                        /* Copy Operand */
                        strlcpy(output_array[m++], s+length, (int)strlen(ch)-length);
                    }
                }
            }
            rewind(mdt);
            flag=0;     /* Coming up code may or maynot be a macro */
            n++;        /* To prevent Macro name from appearing in the output */
        }
        else {  /* Not a macro */
            strcpy(output_array[m++],out_file[n++]);
        }
    }
    
    for(j=0;j<m;j+=3) {
        if(strchr(output_array[j+1], ',')==0) {
            /* If no comma */
            if((j+2)<m) {
                fprintf(out,"%s\t%s\t%s\n",output_array[j],output_array[j+1],output_array[j+2]);
            }
            else {
                /* To prevent a * from being printed at the END of aray */
                fprintf(out,"%s\t%s\n",output_array[j],output_array[j+1]);
            }
        }
        else {
            /* If we have a comma then no TAB space in between */
            fprintf(out,"%s\t%s%s\n",output_array[j],output_array[j+1],output_array[j+2]);
        }
    }
    
    /* Close all files */
    fclose(input);
    fclose(mnt);
    fclose(mdt);
    fclose(out);
    return 0;
}