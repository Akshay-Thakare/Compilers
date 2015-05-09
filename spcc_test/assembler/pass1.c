#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	FILE *mot,*input,*output,*ST,*BT;
	input = fopen("INPUT","r");
	output = fopen("OUTPUT","w");
	ST = fopen("ST","w");
	BT = fopen("BT","w");
	
	int location_counter=0,base_value,base_reg;
	char label[10],opcode[10],operand[10], *brkb;;

	fscanf(input,"%s\t%s\t%s",label,opcode,operand);

	if(strcmp(opcode,"START")==0){
		location_counter = atoi(operand);
		fprintf(output,"%d\n",location_counter);
		
		fscanf(input,"%s\t%s\t%s",label,opcode,operand);
		if(strcmp(opcode,"USING")==0){
			fprintf(output,"%d\n",location_counter);
			
			//By default * is considered as 0 when using atoi
			base_value = atoi(strtok_r(operand, ",", &brkb));
			base_reg = atoi(strtok_r(NULL, ",", &brkb));
			
			int j;
			for(j=0;j<16;j++)
				if(j==base_reg)
					fprintf(BT,"Y\t%d\t%d\n",base_value,j);
				else
					fprintf(BT,"N\t0\t%d\n",j);
			
			fscanf(input,"%s\t%s\t%s",label,opcode,operand);
			while(strcmp(opcode,"END")!=0){
				
				if(strcmp(opcode,"DC")==0){				
					char *type = strtok_r(operand, "'", &brkb);
					int val = atoi(strtok_r(NULL, "'", &brkb));
					fprintf(ST,"%s\t%d\t%d\n",label,val,location_counter);
				
					fprintf(output,"%d\t%s\t%s\t%d\n",location_counter,label,opcode,val);
					
					if(strcmp(type,"HW")==0)
						location_counter+=2;
					if(strcmp(type,"F")==0)
						location_counter+=4;
						
				} else if(strcmp(opcode,"DS")==0){
					fprintf(ST,"%s\t%d\t%d\n",label,-1,location_counter);
					fprintf(output,"%d\t%s\t%s\t_\n",location_counter,label,opcode);
					location_counter+=4;
				} else if(strcmp(label,"**")==0){
					fprintf(output,"%d\t**\t%s\t%s\n",location_counter,opcode,operand);
					location_counter+=4;
				}				
				fscanf(input,"%s\t%s\t%s",label,opcode,operand);
			}
		}	
		fprintf(output,"%d\t%s\n",location_counter,opcode);
	}
	return 0;
}
