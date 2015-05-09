%{
#include<stdio.h>
int constants=0, operators=0, relational_op=0,special_sym=0;
%}

%%
[0-9]* constants++;
[-+*/%]+ operators++;
[=!><]+ relational_op++;
[\[\](){},\;:*…=#]* special_sym++;
%%
int main(){
printf ("This Lex program counts the number of constants,etc in ");
printf ("given text.");
printf ("\nEnter the text and terminate it with CTRL-d.\n");
yylex();
printf ("Constants = %d, Operators = %d, Relational operators = %d, Special Symbols = %d.\n", constants, operators, relational_op,special_sym);
return 0;
}
