#include <stdio.h>

int main(void){
	char buffer[100];
	while(1){
		printf("> ");
		fgets(buffer, sizeof(buffer), stdin);
		printf("Escribiste: %s", buffer);
	}
	return 1;
}
