#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#define max 50

struct Stack{ 
	int top; 
	unsigned capacity; 
	int* array; 
}; 

struct Stack* createStack( unsigned capacity ){ 
	struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack)); 
	stack->top = -1; 
	stack->capacity = capacity; 
	stack->array = (int*) malloc(stack->capacity * sizeof(int));  
	return stack; 

	int bool;
}

void push(struct Stack* stack,int op){ 
	stack->array[++stack->top] = op; 
}

int pop(struct Stack* stack){ 
	return stack->array[stack->top--];
} 

int isEmpty(struct Stack* stack){ 
	return stack->top == -1 ; 
}

char peek(struct Stack* stack){ 
	return stack->array[stack->top]; 
}

int Prec(int ch){ 
	switch (ch){ 
	case 43: 
	case 45: 
		return 1; 
	case 42: 
	case 47: 
		return 2;
	case 40:
	case 41:
		return 3;
	} 
} 

int Prec2(char ch){ 
	if(ch=='+' || ch=='-'){
		return 1;
	}else if(ch=='*' || ch=='/'){
		return 2;
	}else{
	return 3;
	}
} 

void printStack(struct Stack* sayi,struct Stack* isaret){
	int i;
	printf("sayi yigini: ");
		for(i=0;i<=sayi->top;i++){
			printf("%d ",sayi->array[i]);
		}
		printf("\t isaret yigini: ");
		for(i=0;i<=isaret->top;i++){
			if(isaret->array[i]==43){
				printf("+ ");
			}else if(isaret->array[i]==45){
				printf("- ");
			}else if(isaret->array[i]==42){
				printf("* ");
			}else if(isaret->array[i]==47){
				printf("/ ");
			}else if(isaret->array[i]==40){
				printf("( ");
			}else if(isaret->array[i]==41){
				printf(") ");
			}		
		}
		printf("\n");
}

int main(){ 
	struct Stack* sayi = createStack(max); 
	struct Stack* isaret = createStack(max); 
	
	char exp[max],*token;
	int i,sayi1,sayi2,islem;
	
	printf("Islemi giriniz:");
	gets(exp);
	
	token=strtok(exp," ");
	
	while(token!=NULL){
		if(atoi(token)){
			push(sayi,atoi(token));
		}else if(token[0]=='('){
					push(isaret,40);
				}else if(token[0]==')'){
					while(peek(isaret)!=40){
						islem=pop(isaret);
						sayi2=pop(sayi);
						sayi1=pop(sayi);
						
						if(islem==43){
							push(sayi,sayi1+sayi2);
						}else if(islem==45){
							push(sayi,sayi1-sayi2);
						}else if(islem==42){
							push(sayi,sayi1*sayi2);
						}else if(islem==47){
							push(sayi,sayi1/sayi2);
						}
						
					}
					islem=pop(isaret);
					
				}else if(isEmpty(isaret) || peek(isaret)==40){
					if(token[0]=='+'){
						push(isaret,43);
					}else if(token[0]=='-'){
						push(isaret,45);
					}else if(token[0]=='*'){
						push(isaret,42);
					}else if(token[0]=='/'){
						push(isaret,47);
					}
				}else{
				
				if(Prec(peek(isaret)) >= Prec2(token[0])){
					while((Prec(peek(isaret)) >= Prec2(token[0])) && (peek(isaret)!=40)){
						islem=pop(isaret);
						sayi2=pop(sayi);
						sayi1=pop(sayi);

						if(islem==43){
							push(sayi,sayi1+sayi2);
						}else if(islem==45){
							push(sayi,sayi1-sayi2);
						}else if(islem==42){
							push(sayi,sayi1*sayi2);
						}else if(islem==47){
							push(sayi,sayi1/sayi2);
						}
						printStack(sayi,isaret);	
					}
					
					if(token[0]=='+'){
						push(isaret,43);
					}else if(token[0]=='-'){
						push(isaret,45);
					}else if(token[0]=='*'){
						push(isaret,42);
					}else if(token[0]=='/'){
						push(isaret,47);
					}
					
				}else if(Prec(peek(isaret)) < Prec2(token[0])){
					if(token[0]=='+'){
						push(isaret,43);
					}else if(token[0]=='-'){
						push(isaret,45);
					}else if(token[0]=='*'){
						push(isaret,42);
					}else if(token[0]=='/'){
						push(isaret,47);
					}
				}
				
			}
		printStack(sayi,isaret);
		token=strtok(NULL," ");
	}
	
	while(isaret->top>-1){
		islem=pop(isaret);
		sayi2=pop(sayi);
		sayi1=pop(sayi);
						
		if(islem==43){
			push(sayi,sayi1+sayi2);
		}else if(islem==45){
			push(sayi,sayi1-sayi2);
		}else if(islem==42){
			push(sayi,sayi1*sayi2);
		}else if(islem==47){
			push(sayi,sayi1/sayi2);
		}
	}
	printStack(sayi,isaret);
 	printf("Sonuc=%d ",sayi->array[sayi->top]);
	return 0; 
} 