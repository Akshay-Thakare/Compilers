#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	FILE *input,*mnt,*mdt;
	input = fopen("INPUT.txt","r");
	mnt = fopen("MNT.txt","w");
	mdt = fopen("MDT.txt","w");
	
	int mntc=0, mdtc=0;
	
	char line[50],line2[10];
	fscanf(input,"%s",line);		//Skipping first line
	fscanf(input,"%s",line);
	fprintf(mnt,"%d\t%s\t%d\n",mntc,line,mdtc);
	
	while((fscanf(input,"%s\t%s",line,line2))!=EOF){
		if(strcmp(line,"MEND")==0)
			break;
		fprintf(mdt,"%d\t%s\t%s\n",mdtc,line,line2);
	}
	
	return 0;
}