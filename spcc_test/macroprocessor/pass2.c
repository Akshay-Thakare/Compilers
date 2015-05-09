#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	FILE *input,*mnt,*mdt,*output;
	input = fopen("INPUT.txt","r");
	mnt = fopen("MNT.txt","r");
	mdt = fopen("MDT.txt","r");
	output = fopen("OUTPUT_F.txt","w");
	
	int mntc,mdtc;
	char macro_name[10];
	fscanf(mnt,"%d\t%s\t%d",&mntc,macro_name,&mdtc);
	
	char label[10],opcode[10],operand[10];
	
	while((fscanf(input,"%s",label))!=EOF)
		if(strcmp(label,"MEND")==0)
			break;
	
	while((fscanf(input,"%s\t%s\t%s",label,opcode,operand))!=EOF){
		if(strcmp(opcode,macro_name)==0){
			int mdtc_current; 
			char l1[10],l2[10];
			while((fscanf(mdt,"%d\t%s\t%s",&mdtc_current,l1,l2))!=EOF)
				if(mdtc_current==mdtc)
					fprintf(output,"%s\t%s\t%s\n","**",l1,l2);
			rewind(mdt);
		} else {
			fprintf(output,"%s\t%s\t%s\n",label,opcode,operand);
		}
	}
	
	return 0;
}