#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*functions*/
void addContact(void *pBuffer, void *pAux);
void listContact(void *pBuffer, void *pAux);
void removeContact(void *pBuffer, void *pAux,void *pRead);
void searchContact(void *pBuffer, void *pAux, void *pRead);
void close (void *pAux);



/* data */
#define NAME (sizeof(char) * 10)
#define AGE (sizeof(int))
#define PHONE (sizeof(int))

/*aux*/
#define OPTION (sizeof(int))
#define COUNTER (sizeof(int))
#define POINTER_MEMORY (sizeof(void **))


/*Heap*/
#define FIRST (sizeof(int))
#define LAST (sizeof(int) + sizeof(void **))

#define NEXT (sizeof(char) * 10 + sizeof(int) + sizeof(int) + sizeof(void **))
#define PREVIOUS (sizeof(char) * 10 + sizeof(int) + sizeof(int))

int main(){

    void *pAux = NULL;
    pAux = malloc(COUNTER + POINTER_MEMORY + POINTER_MEMORY);

    *(int *)(pAux) = 0;

    void *pBuffer = NULL;
    pBuffer = malloc(OPTION + POINTER_MEMORY);

    void *pRead = NULL;

    if (!pBuffer || !pAux){
        printf ("\nNao ha memoria suficiente.\n");
        printf ("____________________________");
        exit(1);
    }
    
    do{
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


        switch (*(int *)(pBuffer)){
        case 1:
            addContact(pBuffer, pAux);                    /* adiciona */
            break;
        case 2:
            removeContact(pBuffer, pAux, pRead);        /* remove */
            break;
        case 3:
            listContact(pBuffer, pAux);                 /*lista*/
            break;
        case 4:
            searchContact(pBuffer, pAux, pRead);          /* busca */
            break;
        case 5:
            printf ("\nPrograma encerrado\n");
            close(pAux);
            free(pBuffer);
            free(pAux);
            exit(0);                                        /* sair */
            break;              
        default:
            printf ("\nOpcao invalida, tente de novo!!!\n");
            break;
        }
    }while ((*(int *)(pBuffer) >= 1) || (*(int *)(pBuffer) <= 5));

}

void close(void *pAux){
    void *pClean= *(void **)(pAux + FIRST);
    int *pCounter = (int *)(pAux);

    if (*pCounter == 0){
        printf("Lista vazia!");
    } else {
        /* Enquanto houver informação no "first" ele segue entrando no laço */
        while (*(void **)(pAux + FIRST) != NULL) {
            pClean = *(void **)(pAux + FIRST); /* pClean recebe a primeira pessoa da lista */
            *(void **)(pAux + FIRST) = *(void **)(pClean + NEXT); /* A primeira recebe a NEXT, como uma substituição, fazendo a fila andar */
            free(pClean);  
            /* free no clean pra eliminar a "FIRST" */

            *pCounter-= 1; 
            /* pCounter ou  (int *)(pAux) é decrementado até o laço ser desfeito e a lista toda ser excluída*/
        }
    }
}

void addContact(void *pBuffer, void *pAux){
    int *pCounter = (int *)(pAux); /* contador */

    void *pData = NULL;
    pData = malloc(NAME + AGE + PHONE + POINTER_MEMORY + POINTER_MEMORY); /* armazena os dados de cada contato e inclui memoria p anterior e proximo */

    void *pDataAux = NULL;

    if (!pData){
        printf ("\n_________________\n");
        printf("Erro na alocacao :(");
        printf ("\n_________________\n");
        exit(1);
    }

    printf ("\t\n__________________________");
    printf("\t\nInsira os dados da pessoa\n\n");

    printf("\tDigite o nome:\n\t ");
    scanf("%s", (char *)pData);
    getchar();

    printf("\tDigite a idade:\n\t ");
    scanf("%d", &*(int *)(pData + NAME));
    getchar();
   
    printf("\tDigite o telefone:\n\t ");
    scanf("%d", &*(int *)(pData + NAME + AGE));
    getchar();

    /* Espaços definidos */
    *(void **)(pData + NEXT) = NULL;   
    *(void **)(pData + PREVIOUS) = NULL;


    /* Contador ainda não incrementado, então se for 0 significa que é a primeira pessoa, consequentemente é a última também */
    if (*pCounter == 0){
        *(void **)(pAux + LAST) = pData;
        *(void **)(pAux + FIRST) = pData;
        
        *pCounter += 1;

        return;
    }


    /* pBuffer atualizado com o endereço da primeira pessoa */
    pBuffer = *(void **)(pAux + FIRST);



    while(pBuffer != NULL){
        /* ordem alfabetica e prioridade na fila */
        if(strcmp((char *)pData, (char *)pBuffer) < 0){  /* implica que stringA < stringB */
            *(void **)(pData + PREVIOUS) = *(void **)(pBuffer + PREVIOUS);
            *(void **)(pData + NEXT) = pBuffer;

            if(*pCounter > 1 && *(void **)(pBuffer + PREVIOUS) != NULL){
                *(void **)(pDataAux + NEXT) = pData;
            }

            *(void **)(pBuffer + PREVIOUS) = pData;

            if(*(void **)(pData + PREVIOUS) == NULL){
                *(void **)(pAux + FIRST) = pData;
            }

            if(*pCounter == 1 && *(void **)(pBuffer + NEXT) == NULL){
                *(void **)(pAux + LAST) = pBuffer;
            }

            *pCounter += 1; 

            return;
        }

        if(*(void **)(pBuffer + NEXT) == NULL){
            pDataAux = pBuffer;
        }

        pBuffer = *(void **)(pBuffer + NEXT);
    }

    *(void **)(pData + PREVIOUS) = pDataAux;
    *(void **)(pDataAux + NEXT) = pData;
    *(void **)(pAux + LAST) = pData;

    *pCounter+= 1;

    return;
}



void removeContact(void *pBuffer, void *pAux, void *pRead){
    int *pCounter = (int *)(pAux);

    if (*pCounter == 0){
        printf("Nao ha nada nesta lista para remover.\n\n");
    } else {
        printf("\nRemovendo o primeiro nome da lista...\n");
        printf ("Removido com sucesso!\n\n");
        pRead = *(void **)(pAux + FIRST);       /* Recebe a FIRST */
        *(void **)(pAux + FIRST) = *(void **)(pRead + NEXT); /* A NEXT passa a ser FIRST */
        free(pRead);  /* Excluo a FIRST */
        *(void **)(pBuffer + PREVIOUS) = NULL; /* Deixo espaço livre na ANTERIOR/PREVIOUS */

        *pCounter-= 1;
    }
}

void listContact(void *pBuffer, void *pAux){
    void *pData = NULL;    /* ponteiro auxiliar apontando pro FIRST*/
    pData = *(void **)(pAux + FIRST);

    int *pCounter = (int *)(pAux);

    if(*pCounter == 0){
        printf ("\n_____________________________________________\n");
        printf("Nao ha nada para ser listado :( tente novamente! \n\n");
    } else {
        printf ("\t\t\n_______________________________________\n");
        printf("\t\tLISTA DE NOMES\n\n");
        while(pData != NULL){
            printf("Nome: %s\n", (char *)pData);
            printf("Idade: %d\n", *(int *)(pData + NAME));
            printf("Numero: %d\n\n", *(int *)(pData + NAME + AGE));

            pData = *(void **)(pData + NEXT);
        }
    }
}

void searchContact(void *pBuffer, void *pAux, void *pRead){
    int *pCounter = (int *)(pAux);

    void *pSearchAux = NULL;
    pSearchAux = malloc(sizeof(char) * 10 );

    pRead = *(void **)(pAux + FIRST);

    if(*pCounter == 0){
        printf("\nNão ha nenhum contato registrado ainda :( \n\n");
        free(pSearchAux);

        return;

    } else {
        printf("Quem voce esta procurando? \n");
        scanf("%s", (char *)pSearchAux);
        getchar();
    
        while(pRead != NULL){
            if(strcmp(pRead ,(char *)pSearchAux) == 0){
                printf ("\nAqui esta os dados do contato :) \n");
                printf ("_________________________________\n");
                printf("Nome: %s\n", (char *)pRead);
                printf("Idade: %d\n", *(int *)(pRead + NAME));
                printf("Numero: %d\n\n", *(int *)(pRead + NAME + AGE));

                free(pSearchAux);
                
                return;
            } else {
                printf ("\nContato nao encontrado :( ");
                free(pSearchAux);
                return;
            }

            pRead = *(void **)(pRead + NEXT);
           
        }
    }

    return;
}