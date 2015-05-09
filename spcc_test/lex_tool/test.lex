%{
	#include <stdio.h>
	int constant=0, op=0, identifier=0, sp=0;
%}
%%
[A-Za-z]([A-Za-z]|[0-9])+	identifier++;
[-+*/%]	op++;
[\[\](){},\;:*=#]	sp++;
[0-9]+	constant++;
%%
int main(){
	yylex();
	printf("\nIdentifier = %d \nConstant = %d \n Special = %d \n Opertors = %d\n",identifier,constant,sp,op);
	return 0;
}