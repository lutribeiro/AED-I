#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPTION (sizeof(int))
#define PEOPLE (sizeof(int))
#define SHOW_LIST (sizeof(int))
#define SEARCH (sizeof(char) * 10)
#define COUNTER (sizeof(int))
#define REMOVE (sizeof(char) * 10)
#define TOTAL (OPTION + PEOPLE + SHOW_LIST + SEARCH + COUNTER + REMOVE)
#define TOTAL2 (OPTION + PEOPLE + SHOW_LIST + SEARCH + COUNTER)
#define TOTAL3 (OPTION + PEOPLE + SHOW_LIST + SEARCH)
#define PERSON_SIZE (OPTION + PEOPLE)


typedef struct{
    char name[10];
    int age;
    int number;
} Pessoa;

Pessoa pessoas[10];

void *addContact(void *pBuffer);
void *removeContact (void *pBuffer);
void listContact (void *pBuffer);
void searchContact (void *pBuffer);


int main(){

void *pBuffer = NULL;

pBuffer = malloc(TOTAL);

if (!pBuffer){
    printf("Erro ao alocar memoria.\n");
    exit(1);
}

*(int *)(pBuffer + OPTION) = 0;
do {
    printf ("\n\n___________________________________________\n");
    printf ("\nINSIRA A OPCAO DESEJA DE ACORDO COM O MENU:");
    printf ("\t\n 1) Adicionar contato;");
    printf ("\t\n 2) Remover contato;");
    printf ("\t\n 3) Listar contatos;");
    printf ("\t\n 4) Buscar contato;");
    printf ("\t\n 5) Sair");
    printf ("\n___________________________________________\n");

    printf ("\nOpcao escolhida: ");
    scanf("%d", (int *)(pBuffer));
    getchar();

    switch (*(int *)(pBuffer))
    {
    case 1:
        pBuffer = addContact(pBuffer);          /* adiciona */
        break;
    case 2:
        pBuffer = removeContact(pBuffer);      /* remove */
        break;
    case 3:
        listContact(pBuffer);
        break;
    case 4:
        searchContact(pBuffer);                 /* busca */
        break;
    case 5:
        free(pBuffer);
        printf ("\nPrograma encerrado\n");
        exit(0);                                 /* sair */
        break;
    default:
        printf ("\nOpcao invalida, tente de novo!!!\n");
        break;
    }


} while ((OPTION >=1)||( OPTION <= 5));

}

void *addContact (void *pBuffer){

    if (*(int *)(pBuffer + OPTION) >= 10) {
        printf ("\n___________________________________________\n");
        printf("A lista atingiu o numero maximo de pessoas!");
        printf ("\n___________________________________________\n");
        return pBuffer;
    } else {
        printf ("\t\n__________________________");
        printf("\t\nInsira os dados da pessoa\n\n");

        printf("\tInsira o nome:  ");
        scanf("%s", (pessoas + *(int *)(pBuffer + OPTION)) -> name);
        getchar();

        printf("\tInsira a idade:  ");
        scanf("%d", &(pessoas + *(int *)(pBuffer + OPTION)) -> age);
        getchar();
    
        printf("\tDigite o telefone:  ");
        scanf("%d", &(pessoas + *(int *)(pBuffer + OPTION)) -> number);
        getchar();

        printf ("\n\n Adicionado a lista com sucesso :) \n\n");
        
        
        *(int *)(pBuffer + OPTION) = *(int *)(pBuffer + OPTION) + 1; //incrementa lista
    }

    return pBuffer;
}

void *removeContact (void *pBuffer){
    if (*(int *)(pBuffer + OPTION) == 0){
        printf("Nao ha nada nesta lista para remover.\n\n");
    } else {
        printf("Digite o nome que queira remover: ");
        scanf("%s", (char *)(pBuffer + OPTION + PEOPLE + SHOW_LIST + SEARCH + COUNTER));
        getchar();

        for(*(int *)(pBuffer + TOTAL3) = 0; *(int *)(pBuffer + TOTAL3) < *(int *)(pBuffer + OPTION); *(int *)(pBuffer + TOTAL3) += 1){ 
            if(strcmp((char *)(pBuffer + TOTAL2), (pessoas + *(int *)(pBuffer + TOTAL3)) -> name ) == 0) {  
                 for(*(int *)(pBuffer + TOTAL) = *(int *)(pBuffer + TOTAL3); *(int *)(pBuffer + TOTAL) < *(int *)(pBuffer + OPTION); *(int *)(pBuffer + TOTAL) += 1){
                    strcpy((pessoas + *(int *)(pBuffer + TOTAL)) -> name, (pessoas + 1 + *(int *)(pBuffer + TOTAL)) -> name);
                    (pessoas + *(int *)(pBuffer + TOTAL)) -> age = (pessoas + 1 + *(int *)(pBuffer + TOTAL)) -> age;
                    (pessoas+ *(int *)(pBuffer + TOTAL)) -> number = (pessoas + 1 + *(int *)(pBuffer + TOTAL)) -> number;
                }
                printf ("\n\n Contato removido com sucesso :) \n\n");

                *(int *)(pBuffer + OPTION) = *(int *)(pBuffer + OPTION) - 1;
                return pBuffer;
            }
        }
        printf ("\n______________________________________\n");
        printf("Nao ha ninguem com esse nome na lista :(\n\n");
    }
    return pBuffer;

}

void listContact(void *pBuffer){
   
    if (*(int *)(pBuffer + OPTION) == 0) {
        printf ("\n_____________________________________________\n");
        printf("Nao ha nada para ser listado :( tente novamente! \n\n");
    } else {
        printf ("\t\t\n______________________\n");
        printf("\t\tLISTA DE NOMES\n\n");
       
        for (*(int *)(pBuffer + PERSON_SIZE) = 0 ; *(int *)(pBuffer + PERSON_SIZE) < *(int*)(pBuffer + OPTION) ; *(int *)(pBuffer + PERSON_SIZE) += 1){
            printf("Contato de posicao [%d] na lista:\n", *(int *)(pBuffer + PERSON_SIZE) + 1);
            printf("\t- Nome: %s\n", (pessoas + *(int *)(pBuffer + PERSON_SIZE)) -> name);
            printf("\t- Idade: %d anos\n", (pessoas + *(int *)(pBuffer + PERSON_SIZE)) -> age);
            printf("\t- Numero: %d\n\n", (pessoas + *(int *)(pBuffer + PERSON_SIZE)) -> number);
        }
    }

}

void searchContact(void *pBuffer){    
    printf("Quem voce esta procurando? \n");
    scanf("%s", (char *)(pBuffer + OPTION + PEOPLE + SHOW_LIST));
    getchar();

    for(*(int *)(pBuffer + TOTAL3) = 0; *(int *)(pBuffer + TOTAL3) <  *(int*)(pBuffer + OPTION); *(int *)(pBuffer + TOTAL3) += 1){
        if(strcmp((char *)(pBuffer + OPTION + PEOPLE + SHOW_LIST), (pessoas + *(int *)(pBuffer + TOTAL3)) -> name ) == 0){
            printf ("\n_____________________________\n");
            printf ("\nVoce esta falando deste contato?\n");
            printf("\t- Nome: %s\n", (pessoas + *(int *)(pBuffer + TOTAL3)) -> name);
            printf("\t- Idade: %d anos\n", (pessoas + *(int *)(pBuffer + TOTAL3)) -> age);
            printf("\t- Numero: %d\n\n", (pessoas + *(int *)(pBuffer + TOTAL3)) -> number);
            return;
        }
    }
    printf("Este nome nao existe na lista :( tente novamente! \n");
    return;
}