#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	FILE *input, *keyword, * operator, *special, *output;
	input = fopen("input.txt","r");
	keyword = fopen("keywords.txt","r");
	operator = fopen("operators.txt","r");
	special = fopen("special_symbols.txt","r");
	output = fopen("output.txt","w");
	
	char line[10],temp[10];
	int flag1=0,flag2=0,flag3=0,flag4=0;
	while((fscanf(input,"%s",line))!=EOF){
		while(fscanf(keyword,"%s",temp)!=EOF)
			if(strcmp(temp,line)==0){
				fprintf(output,"%s\t%s\n",line,"keyword");
				flag1=1;
			}
		if(flag1==0)
			while(fscanf(operator,"%s",temp)!=EOF)
				if(strcmp(temp,line)==0){
					fprintf(output,"%s\t%s\n",line,"operator");
					flag2=1;
				}
		if(flag1==0 && flag2==0)
			while(fscanf(special,"%s",temp)!=EOF)
				if(strcmp(temp,line)==0){
					fprintf(output,"%s\t%s\n",line,"special symbol");
					flag3=1;
				}
		if(flag1==0 && flag2==0 && flag3==0 && isdigit(line[0])){
			fprintf(output,"%s\t%s\n",line,"constant");
			flag4=1;
		}
		
		if(flag1==0 && flag2==0 && flag3==0 && flag4==0)
			fprintf(output,"%s\t%s\n",line,"identifier");
			
		flag1=0;flag2=0;flag3=0;flag4=0;	//Rest flags
		rewind(keyword);
		rewind(operator);
		rewind(special);
	}
	
	return 0;
}