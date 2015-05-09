//harrenhal destruction :P

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    char rev[100],harren[100];
    int i,t,count;
    
    scanf("%d",&t);
    for(i=0;i<t;i++)
    {
        count=0;
        scanf("%s",harren);
        strcpy(rev, harren);
        int j;
        for(j=0;j<strlen(harren);j++)
        {
            rev[j]=harren[strlen(harren)-j-1];
        }
        rev[j]='\0';
        
        for(j=0;j<sizeof(rev);j++)
        {
            if(harren[i]==rev[i])
                count++;
        }
        if(count==sizeof(harren))
            printf("1");
        else
            printf("2");
    }
    
    
    return 0;
}