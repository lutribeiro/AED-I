/* Luísa Ribeiro - lutribeiro@inf.ufpel.edu.br - Engenharia de Computação - 20103614
Faça um programa que armazena nomes. O programa deve armazenar todos os nomes na mesma string.
O tamanho da string deve crescer e diminuir conforme nomes forem colocados ou removidos. 
Não pode ter desperdício de memória.
Faça o seguinte menu:
1) Adicionar nome
2) Remover nome
3) Listar
4) Sair */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *adiciona_semicolon(char *name){
    int i = strlen(name) + 1;

	name = (char *)realloc(name, sizeof(char) * i + 1);
	if(!name){
			printf("\nErro ao alocar memoria!\n");
        	return NULL;
	}

	name[i - 1] = ';';
	name[i] = '\0';
	return name;
}

char *get_name(char *name, int i){
    do{
		i++;
		name = (char *)realloc(name, sizeof(char) * i + 1);
		if(!name){
			printf("\nErro ao alocar memoria!\n");
        	return NULL;
		}
		name[i - 1] = getchar();
	} while(name[i - 1] != '\n');

	name[i - 1] = '\0';
	return name;
}

char *adc_name(char *name){	
    int length = strlen(name);
	printf("\nDigite o nome que deseja inserir: ");
	name = get_name(name, length);
	name = adiciona_semicolon(name);
	return name;
}

char *removeName(char *name){
	int i = 0;
	char temp[100], temp2[100];

	char *name_comp = (char *)malloc(sizeof(char));
	if (!name_comp) {
        printf("\nErro ao alocar memoria!\n");
        return NULL;
    }

    printf("\nDigite o nome que deseja remover: ");	
	name_comp = get_name(name_comp, i);
	name_comp = adiciona_semicolon(name_comp);
	char *p = strstr(name, name_comp); //guarda o endereço da primeira ocorrencia do nome na string

	if(!p){
		printf("\nNome nao encontrado!\n");
		return NULL;
	} else {
		strcpy(temp, name);
		temp[p - name] = '\0';
		strcpy(temp2, p + strlen(name_comp));
   		strcat(temp, temp2);
    	strcpy(name, temp);
		//o seguinte teste evita erro no caso de dar outra instrução após a remoção de todos os nomes ja existentes
			if (strlen(name) == 0){
				name = (char *)realloc(name, sizeof(char) + 1);
			} else {
				name = (char *)realloc(name, sizeof(char) * strlen(name) + 1);
			}
	}

	printf("\nNome removido!\n");
	free(name_comp);
	return name;
}

int list_names(char *name){
	int i = 0;

	if(name[0] == '\0'){
		printf("\nNao existem nomes no registro!\n");
		return 1;
	}

	printf("\nNomes registrados: \n");

	while(name[i] != '\0'){

		if(name[i] == ';'){
			printf("\n");
		} else {
			printf("%c", name[i]);
		}
		i++;
	}
	return 0;
}

int menu(void){
	int aux = 0;

	do {
		printf("\n*** MENU ***\n\n");
		printf("1) Adicionar nome\n");
		printf("2) Remover nome\n");
		printf("3) Listar\n");
		printf("4) Sair\n");
		printf("--> Digite sua escolha: ");
		scanf("%d", &aux);
	} while (aux <= 0 || aux > 4);
	getchar();
	return aux;
}

int main(int argc, char *argv[]){
    int op=0;

    char *p = (char *)malloc(sizeof(char));
    if (!p) {
        printf("\nErro ao alocar memoria!\n");
        return 1;
    }
    *p = '\0';

    while(op != 4) {
		op = menu();
		switch (op) {
		case 1:
			p = adc_name(p);
			break;
		case 2:
			p = removeName(p);
			break;
		case 3:
			list_names(p);
			break;
		case 4:
			break;
        default: 
            printf ("Opcao Invalida!");
            break;
		}
	}

    free(p);
	return 0;
}