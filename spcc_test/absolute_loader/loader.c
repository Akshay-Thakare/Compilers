#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	int curloc, start, length, n=0,count=0;
	char card[10], name[10];
	FILE *input, *output;
	input = fopen("INPUT.txt","r");
	output = fopen("OUTPUT.txt","w");

	fscanf(input,"%s%s%x%x",card,name,&start,&length);	//H card

	fprintf(output,"\n%x :",start);
	while(1){
		fscanf(input,"%s",card);		
		if(strcmp(card,"E")==0)
			break;
		else if(strcmp(card,"T")==0)
			fscanf(input,"%x %x",&curloc,&length);
		else {
			while(start!=curloc){
				if(count==16){
					fprintf(output,"\n%x : ",start);
					count=0;
				}
				else if(!(count%4))
					fprintf(output," ");
				fprintf(output,"XX");
				start++;
				count++;
			}
			n=0;
			while(n<strlen(card)){
				if(count==16){
					fprintf(output,"\n%x : ",start);
					count=0;
				}
                else if(!(count%4))
					fprintf(output," ");
				start++;
				count++;
				curloc++;
				fprintf(output,"%c%c",card[n],card[n+1]);
				n+=2;
			}
		}
	}
	return 0;
}