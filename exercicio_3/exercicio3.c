/*Luisa Treptow Ribeiro */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void *addContact(void *pBuffer);
void *removeContact (void *pBuffer);
void listContact (void *pBuffer);
void searchContact (void *pBuffer);

#define NAMECONTACT (sizeof(char) * 10)
#define AGECONTACT sizeof(int)
#define PHONECONTACT sizeof(int)
#define COUNTER sizeof(int)


int main(){
	int option;

	void *pBuffer = NULL;

	pBuffer = malloc(NAMECONTACT); // alocação de memória necessária
	
	*(int *)pBuffer = 0;
	
	if (pBuffer == NULL){
		printf ("\n***ERRO NA ALOCAÇÃO DE MEMÓRIA***\n");
		exit(1);
	}


	do{
		printf ("\n\n** MENU DE OPCOES **\n");
		printf ("\n 1) Adicionar nome ");
		printf ("\n 2) Remover nome ");
		printf ("\n 3) Listar nome ");
		printf ("\n 4) Buscar nome ");
		printf ("\n 5) Sair ");

		printf ("\n Opcao escolhida: ");
		scanf ("%d", &option);
		printf ("\n---------------------------\n");
		switch (option)
		{
		case 1:
			pBuffer = addContact (pBuffer);
			break;
		case 2:
			pBuffer = removeContact (pBuffer);
			break;
		case 3:
			listContact(pBuffer);
			break;
		case 4:
			searchContact (pBuffer);
			break;
		case 5:
			free (pBuffer);
			exit (0);
			break;
		
		default:
			printf ("\n**OPCAO INVALIDA, TENTE DE NOVO**\n");
			break;
		} 
	} while ((option >= 1) || (option <= 5));
}


void *addContact (void *pBuffer){
	int total;

	getchar();

	total = *(int *)pBuffer;

	pBuffer = realloc(pBuffer, COUNTER + (NAMECONTACT + AGECONTACT + PHONECONTACT) * (total + 1));

	if (pBuffer == NULL){
		printf ("\n***NAO HA MEMORIA***\n");
		exit(1);
	}

	printf("\n\n ***** INSIRA OS DADOS ***** \n");

	printf ("Nome do contato: ");
	scanf("%s", (char *)(pBuffer + COUNTER + (NAMECONTACT + AGECONTACT + PHONECONTACT) * total));
	getchar();

	printf ("Idade: ");
	scanf("%d", (int *)(pBuffer + COUNTER + NAMECONTACT + (NAMECONTACT + AGECONTACT + PHONECONTACT) * total));
    getchar();

	printf ("Numero de telefone: ");
	scanf("%d", (int *)(pBuffer + COUNTER + NAMECONTACT + AGECONTACT + (NAMECONTACT + AGECONTACT + PHONECONTACT) * total));
	getchar();

	*(int *)pBuffer = total + 1;

	return pBuffer;
}

void *removeContact (void *pBuffer){
	int indexList, j, i;
    char remove_contact[10];

    indexList = *(int *)pBuffer;

    if (indexList == 0){
        printf("** NAO HA CONTATOS NA LISTA, INSIRA ALGUNS! **\n\n");
    } else {
        printf("** Insira o nome do contato que deseja excluir:  ");
        scanf("%s", remove_contact);
        getchar();

        for(i = 0; i < indexList; i++){
            if(strcmp((char *)pBuffer + COUNTER + ((NAMECONTACT + AGECONTACT + PHONECONTACT) * i), remove_contact) == 0) {
                for(j = i; j < indexList; j++){
                    strcpy((char *)pBuffer + COUNTER + ((NAMECONTACT + AGECONTACT + PHONECONTACT) * j), (char *)pBuffer + COUNTER + (NAMECONTACT + AGECONTACT + PHONECONTACT) * (j + 1));
                    *(int *)(pBuffer + COUNTER + NAMECONTACT + ((NAMECONTACT + AGECONTACT + PHONECONTACT) * j)) = *(int *)(pBuffer + COUNTER + NAMECONTACT + (NAMECONTACT + AGECONTACT + PHONECONTACT) * (j + 1));
                    *(int *)(pBuffer + COUNTER + NAMECONTACT + AGECONTACT + ((NAMECONTACT + AGECONTACT + PHONECONTACT * j))) = *(int *)(pBuffer + COUNTER + NAMECONTACT + AGECONTACT + (NAMECONTACT + AGECONTACT + PHONECONTACT) * (j + 1));
                }
                *(int *)pBuffer = indexList - 1;
                pBuffer = realloc(pBuffer, COUNTER + (NAMECONTACT + AGECONTACT + PHONECONTACT) * (indexList - 1));
                return pBuffer;
            }
        }
        printf("*** ERRO: NOME NAO EXISTENTE NESTA LISTA\n\n");
    }
    return pBuffer;
	
}

void listContact (void *pBuffer){
	int indexList, i;

	indexList = *(int *)pBuffer;

	if (indexList == 0){
		printf ("\n**********************\n");
		printf ("\n Nao ha contatos nessa agenda. Insira um contato.\n");
	}else {
		for (i=0; i<indexList; i++){
			printf("\n\n*Contato de numero: [ %d ]", i + 1);
			printf ("\n*Nome: %s\n", (char *)pBuffer + COUNTER + (NAMECONTACT + AGECONTACT + PHONECONTACT) * i);
			printf ("\n*Idade: %d\n", *(int *)(pBuffer + COUNTER + NAMECONTACT + (NAMECONTACT + AGECONTACT + PHONECONTACT) * i));
			printf ("\n*Numero: %d\n", *(int *)(pBuffer + COUNTER + NAMECONTACT + AGECONTACT + (NAMECONTACT + AGECONTACT + PHONECONTACT) * i));	
		}
	}
}



void searchContact (void *pBuffer){
	int indexList, i;
    char search_NAMECONTACT[10];
    
    printf("\n\n**Insira o nome do contato buscado: \n");
    scanf("%s", search_NAMECONTACT);
    getchar();

    indexList = *(int *)pBuffer;

    for(i = 0; i < indexList; i++){
        if(strcmp((char *)pBuffer + COUNTER + (NAMECONTACT + AGECONTACT + PHONECONTACT) * i , search_NAMECONTACT) == 0){
            printf("\nNome: %s\n", (char *)pBuffer + COUNTER + (NAMECONTACT + AGECONTACT + PHONECONTACT) * i);
            printf("\nIdade: %d\n", *(int *)(pBuffer + COUNTER + NAMECONTACT + (NAMECONTACT + AGECONTACT + PHONECONTACT) * i));
            printf("\nNumero: %d\n", *(int *)(pBuffer + COUNTER + NAMECONTACT + AGECONTACT + (NAMECONTACT + AGECONTACT + PHONECONTACT) * i));
            return;
        }
    }
    printf("\n *** NAO HA REGISTRO DESTE NOME NA LISTA ***\n");
    return;

}