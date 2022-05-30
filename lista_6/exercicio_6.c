#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define MAX 100000

/* 

A Implementação será feita com a função gettimeofday()  
https://levelup.gitconnected.com/8-ways-to-measure-execution-time-in-c-c-48634458d0f9

*/

void insertionSort (int *v, int n);
void selectionSort(int *v, int n);
void quickSort(int *v, int left, int right);
void mergeSort(int *v, int left, int right);
void merge (int *v, int left, int mid, int right);
void verifyAndPrint (int *v, int n);
void *auxiliar (int *v, int n); 
void readNotOrdered (int *v, int n);



int main(){

    int n=0, i=0, option=0;
    int *v = NULL;
    int *vAux = NULL;

    
    struct timeval begin, end;
    float elapsed;

    printf ("\nInsira um numero N para indicar o tamanho do vetor: ");
    scanf ("%d", &n);
    
    v = malloc(n * sizeof(int));

    srand(time(NULL)); 
    for (i=0; i<n; i++){
        v[i] = (rand() % MAX);
    }

   
    readNotOrdered(v, n);
    printf ("\n----------------------------------------------------------------------------------------------------------------");

    do{
        printf ("\nEscolha qual algoritmo deseja usar: \n");

        printf ("\n- MENU -\n");
        printf ("1) Insertion Sort;\n");
        printf ("2) Selection Sort;\n");
        printf ("3) Quick Sort;\n");
        printf ("4) Merge Sort; \n");
        printf ("5) Sair\n");
        printf ("Insira aqui a opcao desejada: ");
        scanf ("%d", &option);
        printf ("\n");
        printf ("---------------------------\n");

        switch (option){
            case 1:
                printf ("\nVoce escolheu: (%d)Insertion Sort!\n", option);
                vAux = auxiliar(v, n);
                
                gettimeofday(&begin, 0);
                insertionSort(vAux, n);
                gettimeofday(&end, 0);

                elapsed = ((end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec))*1e-6;
                /* long seconds = end.tv_sec - begin.tv_sec;
                long microseconds = end.tv_usec - begin.tv_usec;
                double elapsed = seconds + microseconds*1e-6; */

                readNotOrdered(v, n);
                verifyAndPrint(vAux, n);

                printf ("\n---------------------------------------------------------------------------");
                printf ("\nO tempo final que o algoritmo - Insertion Sort - levou para ser computado foi de: %.8f s", elapsed);

                elapsed = 0;
                free(vAux);
                break;
            case 2:
                printf ("\nVoce escolheu: (%d)Selection Sort!\n", option);
                vAux = auxiliar(v, n);
                
                gettimeofday(&begin, 0);
                selectionSort(vAux,n);
                gettimeofday(&end, 0);
                
                elapsed = ((end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec))*1e-6;

                readNotOrdered(v, n);
                verifyAndPrint(vAux, n);
                
                printf ("\n---------------------------------------------------------------------------");
                printf ("\nO tempo final que o algoritmo - Selection Sort - levou para ser computado foi de: %.8f s", elapsed);

                free(vAux);
                break;
            case 3:
                printf ("\nVoce escolheu: (%d)Quick Sort!\n", option);
                vAux = auxiliar(v, n);
                
                gettimeofday(&begin, 0);
                quickSort(vAux, 0, n - 1);
                gettimeofday(&end, 0);
                
                elapsed = ((end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec))*1e-6;

                readNotOrdered(v, n);
                verifyAndPrint(vAux, n);
                
                printf ("\n---------------------------------------------------------------------------");
                printf ("\nO tempo final que o algoritmo - Quick Sort - levou para ser computado foi de: %.8f s", elapsed);

                free(vAux);
                break;
            case 4:
                printf ("\nVoce escolheu: (%d)Merge Sort! \n", option);
                vAux = auxiliar(v, n);            
                
                gettimeofday(&begin, 0);
                mergeSort (vAux, 0, n-1);
                gettimeofday(&end, 0);

                elapsed = ((end.tv_sec - begin.tv_sec) + (end.tv_usec - begin.tv_usec))*1e-6;

                readNotOrdered(v, n);
                verifyAndPrint(vAux, n);
                
                printf ("\n---------------------------------------------------------------------------");
                printf ("\nO tempo final que o algoritmo - Merge Sort - levou para ser computado foi de: %.8f s", elapsed);

                free(vAux);
                break;
            case 5:
                free(v);
                exit(0);
                break;
            default:
                printf ("\nOPÇAO INDISPONIVEL! Tente novamente :) \n");
                break;
            }

    }while (option>=1 || option <=5);
}

void *auxiliar (int *v, int n){
    int i, *vAux;

    vAux = NULL;
    vAux = malloc(n * sizeof(int));
    for (i=0; i<n; i++){
        vAux [i]= v[i];
    }
    return vAux;
}

void readNotOrdered (int *v, int n){
    int i;
    printf("\nSEQUENCIA NAO ORDENADA: ");
    for (i=0; i<n; i++){
        printf ("| %d ", v[i]);    
    }
}

void verifyAndPrint (int *v, int n){
    int i, j, c=0;
    for (i=0; i<n; i++){
        if ((v[i] < v[i+1]) || (v[i]==v[i+1])){
            c++;
            printf ("\nEstava uma bagunca, mas agora ja esta tudo no seu devido lugar:) confira abaixo: \n");
        }
        if (c!=0){
            for(i = 0; i < n; i++) {
                 printf("%d°- %d\n", (i+1), v[i]);
            }
            return;
        }
    }
    printf ("\nO vetor NAO foi ordenado :(\n");
}

void insertionSort(int *v, int n){
   
    int i, tmp, j;
    for (i = 1; i < n; i++){
        tmp = v[i];
        j = i - 1;

        while (j >= 0 && v[j] > tmp){
            v[j + 1] = v[j];
            j = j - 1;
        }
        
        v[j + 1] = tmp;
    }
}
 
void selectionSort( int *v, int n) {
    int min,tmp,i,j,min_id;
    
    min_id = 0;

    for(i=0; i<n-1; i++) {
        min = v[i];
        for(j=i+1; j<n; j++)
            if(v[j] < min) {
                min = v[j];
                min_id = j;
                }
            tmp = v[i];
            v[i] = v[min_id];
            v[ min_id] =tmp;
            min_id = i+1;
    } 
}

void quickSort (int *v, int left, int right) {
    int mid,tmp,l,r;
    
    l = left;
    r = right ;
    mid = v[(left + right)/2];

    do {
        while (v[l] < mid) 
            l++;
        while(mid< v[r])
            r--;
        if(l <= r) {
            tmp = v[l];
            v[l] = v[r];
            v[r] = tmp;
            l++;
            r--;
        }
    } while(l <= r);
    if(left< r)
        quickSort(v,left,r);

    if(l <right)
        quickSort(v,l,right);

}

void mergeSort (int *v, int left, int right) {
    int mid;

    if (left < right) {
        mid = ((left + right) / 2);
        mergeSort(v, left, mid);
        mergeSort(v, mid + 1, right);
        merge(v, left, mid, right);
    }
    
    return;
}

void merge(int *v, int left, int mid, int right) {
    int i, j, k, sizeAux, *aux, p1, p2; 
    int final1=0, final2=0;
    
    //tamanho do vetor aux
    sizeAux = right - left + 1;
    
    //vetores divididos
    p1 = left;
    p2 = mid + 1;
    aux = (int *)malloc(sizeof(int) * sizeAux);

    if(aux != NULL) {
    //para cada posição do vetor aux, testa qual o elemento maior entre os vetores divididos
        for(i = 0; i < sizeAux; i++) {
            //roda o seguinte bloco caso nenhum dos vetores divididos tenha chegado ao final
            if(!final1 && !final2) {
                if(v[p1] < v[p2]) {
                    aux[i] = v[p1++];
                } else {
                    aux[i] = v[p2++];
                }
                //testa se algum dos vetores divididos acabou de chegar ao final
                if(p1 > mid) {
                    final1 = 1;
                }
                if(p2 > right) {
                    final2 = 1;
                }
            } else { 
                //copia para o final o que sobrou
                if(!final1) {
                    aux[i] = v[p1++];
                } else {
                    aux[i] = v[p2++];
                }
            }
        }
        //copia do vetor aux para o original, ja de forma ordenada
        for(j = 0, k = left; j < sizeAux; j++, k++) {
            v[k] = aux[j];
        }
    }
    
    free(aux);
    return;
}