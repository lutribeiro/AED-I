#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char name[30];
    int age;
    int stature;
} Pessoa;


void finishList(int counter, Pessoa *pPessoa);
void *addMember(int counter, Pessoa *pPessoa);

int main(){

int counter = 0, option;
Pessoa *pPessoa = NULL;


do {
        printf ("\n-----------------------------------");
        printf ("\nInsira a opcao que deseja seguir: ");
        printf ("\n-----------------------------------\n");
        printf ("\n 1)Inserir pessoa na lista;");
        printf ("\n 2)Listar e sair;");
        
        printf ("\n\nOpcao escolhida: ");
        scanf("%d", &option);
        getchar();
        printf ("-------------------\n");

        switch (option)
        {
        case 1:
            pPessoa = addMember(counter, pPessoa);
            counter++;
            break;
        case 2:
            finishList(counter, pPessoa);
            free(pPessoa); //limpa
            exit(0);
            break;
        default:
            printf ("\n\nOpcao invalida, tente novamente :) ");
            break;
        }
    }while ((option >= 1) || (option <= 2));

}


void *addMember(int counter, Pessoa *pPessoa){
    
    if(counter != 0){ 
        pPessoa = (Pessoa *)realloc(pPessoa, sizeof(Pessoa) * (counter+ 1));
    } else { 
        pPessoa = (Pessoa *)malloc(sizeof(Pessoa));
    }


    printf ("\nInsira o nome da pessoa: \n");
    scanf ("%s", (pPessoa + counter) -> name);
    getchar();
    
    printf ("-----------------------------");
    
    printf ("\nInsira agora a idade: \n");
    scanf ("%d", &(pPessoa + counter) -> age);
    getchar();
    
    printf ("-----------------------------");
    
    printf ("\nInsira a altura dela (em cm): \n");
    scanf ("%d", &(pPessoa + counter) -> stature);
    getchar();

    printf ("-----------------------------");

    return pPessoa;
}

void finishList(int counter, Pessoa *pPessoa){
    
    int i;

    if (counter == 0){
        printf ("\n--------------");
        printf ("\n Lista vazia!\n");
        printf ("--------------");
    } else {
        printf ("\nA lista de dados de cada pessoa aparecera a seguir e logo após o programa irá encerrar");
        printf ("\n----------------------------------------------------------------------------------------\n");

        for (i=0; i<counter; i++){
            printf ("\n\t---------------");
            printf ("\n\t NOME: %s\n", (pPessoa + i) -> name);
            printf ("\t IDADE: %d anos\n", (pPessoa + i) -> age);
            printf ("\t ALTURA: %d cm\n", (pPessoa + i) -> stature);
            
        }
    }
}

