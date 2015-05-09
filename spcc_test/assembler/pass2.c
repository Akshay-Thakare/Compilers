#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	FILE *input,*mot,*output,*bt,*st;
	input = fopen("OUTPUT","r");
	mot = fopen("MOT","r");
	st = fopen("ST","r");
	bt = fopen("BT","r");
	output = fopen("OUTPUT_F","w");
	
	char check[10];
	int base_reg,base_val;
		
	while((fscanf(bt,"%s\t%d\t%d",check,&base_val,&base_reg))!=EOF)
		if(strcmp(check,"Y")==0)
			break;

	int location;
	char label[10],opcode[10], operand[10],*symbol, *brkb;
	fscanf(input,"%d",&location);
	fprintf(output,"%d\n",location);
	fscanf(input,"%d",&location);
	fprintf(output,"%d\n",location);
	
	while((fscanf(input,"%d\t%s\t%s\t%s",&location,label,opcode,operand))!=EOF){
		if(strcmp(label,"**")==0){
		
			//opcode,operand
			int flag=0,temp,line_no=0;
			char mn[10],op[10];
			while((fscanf(mot,"%s\t%s",mn,op))!=EOF){
				if(strcmp(opcode,mn)==0){
					flag=1;
					break;
				}
			}
			
			int val = atoi(strtok_r(operand, ",", &brkb));
			symbol = strtok_r(NULL, ",", &brkb);
			
			if(flag==1){
				flag=0;
				while((fscanf(st,"%s\t%d\t%d",mn,&temp,&line_no))!=EOF){
					if(strcmp(mn,symbol)==0){
						flag=1;
						break;
					}
				}
			}
			
	fprintf(output,"%d\t%s\t %d,%d(%d,%d) \n",location,op,val,line_no,base_val,base_reg);
			rewind(mot);
			rewind(st);
			
		} else {
			if(strcmp(label,"END")==0){
				fprintf(output,"%d\n",location);
				break;
			}
			fprintf(output,"%d\t%s\n",location,operand);
		}
	}
	return 0;
}