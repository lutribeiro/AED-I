# AED-I
Repositório da disciplina de Algoritmos e Estruturas de Dados I do curso de Engenharia de Computação da UFPel

Luísa Treptow Ribeiro

Engenharia de Computação 

Matrícula 20103614


Link do Drive com videos explicativos: https://drive.google.com/drive/folders/1XAWGge1BeKePbCBW9CgsCxTDHYGN6mel?usp=sharing


Link Github: https://github.com/lutribeiro/AED-I

Lista 1
    Exercicio_1
        Hello World
    
    Exercicio_2
        Faça um programa que armazena nomes. O programa deve armazenar todos os nomes na mesma string.
        O tamanho da string deve crescer e diminuir conforme nomes forem colocados ou removidos. 
        Não pode ter desperdício de memória.
        Faça o seguinte menu:
        1) Adicionar nome
        2) Remover nome
        3) Listar
        4) Sair 
    
    Exercicio_3
        Faça uma agenda capaz de incluir, apagar, buscar e listar quantas pessoas o usuário desejar, porém, toda a informação
        incluída na agenda deve ficar num único lugar chamado: “void
        *pBuffer”. Não pergunte para o usuário quantas pessoas ele vai incluir.
        Não pode alocar espaço para mais pessoas do que o necessário.
        Cada pessoa tem nome[10], idade e telefone.
        O trabalho que vale nota será uma continuação deste.

    Exercicio_5
        • Faça um programa que armazene a informação de várias pessoas.
            typedef struct {
                    char nome[30];
                    int idade;
                    int altura;
            }Pessoa;
        • O programa só deve sair quando o usuário disser que não
        deseja mais entrar com os dados de outra pessoa.
        • Antes de sair o programa deve apresentar, de forma
        organizada, os dados de todas as pessoas.

    Exercicio_7
    1. O programa deve armazenar no máximo 10 pessoas
    2. Todas as variáveis que forem usadas no programa deve ser ponteiros. A única exceção é o
    item 1 que deve ser uma variável global Pessoa pessoas[10].
            1. Os ponteiros devem apontar para um buffer chamado pBuffer
            onde os dados devem ser armazenados. 
            Por exemplo, um contador para um for deve ser um ponteiro para int
            e o int vai ficar armazenado dentro de pBuffer.
            2. Não pode usar struct dentro do pBuffer
    3. Como sempre, entregar o código e o vídeo explicando o código, mostrando casos de
    teste e o resultado do DrMemory