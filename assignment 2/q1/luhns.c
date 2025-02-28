#include <stdio.h>
#include <stdlib.h>

int doubledigit(int previous_Char){
	previous_Char*=2;
	if (previous_Char>9){
		previous_Char-=9;
	}
	return previous_Char;
}


int main() {
	char current_Char=getchar();
	char previous_Char=current_Char;
	int y=1;
	int sum1=0;
	int sum2=0;
	char check_digit;
	int remainder;
	current_Char=getchar();

	while (current_Char<='9' && current_Char>='0'){
		if (y==1){
			sum1+=previous_Char-'0';
			sum2+=doubledigit(previous_Char-'0');
		}
		else {
			sum1+=doubledigit(previous_Char-'0');
			sum2+=previous_Char-'0';
		}
		y*=-1;
		previous_Char=current_Char;
		current_Char=getchar();
	}
	check_digit=previous_Char;

	if (y==1){
		sum1*=9;
		remainder=sum1%10;
	}
	else {
		sum2*=9;
		remainder=sum2%10;
	}
	if (remainder!=(check_digit-'0')){
		printf("Invalid\n");
	}
	else{printf("Valid\n");}
}